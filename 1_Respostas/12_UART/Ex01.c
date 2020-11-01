#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>
#include <string.h>

// RPi 0, 1 e 2
// #define TTY "/dev/ttyAMA0"
// RPi 0W, 3 e 4
#define TTY "/dev/ttyS0"

#define VECTOR_LENGTH   100

int uart0_fd;

int  get_raw(void)
{
    int raw = 0;
    unsigned char msp430_input = 0;

    for (int i=0; i<2; i++)
	{
		msp430_input = (unsigned char)serialGetchar(uart0_fd);

        if (serialDataAvail(uart0_fd) == -1)
        {
			printf("ERROR - [%s]\n", strerror(errno));
            
            raw = 0;
            
            break;
        }

        if (i == 0)
            raw += msp430_input;
        else
            raw += (msp430_input << 8);
	}

    return raw;
}

void average(int *ptr)
{
    float voltage, av = 0;

    for (int i=0; i<VECTOR_LENGTH; i++)
        av += (float)ptr[i] / VECTOR_LENGTH;

    voltage = av * (3.3 / 1024);

    printf("MSP430 A/D Voltage average = %.2f\n", voltage);
}

void ctrl_c(int sig)
{
	puts("\nFechando " TTY "...");

	serialClose(uart0_fd);

	exit(0);
}

int main(void)
{

	signal(SIGINT, ctrl_c);

	uart0_fd = serialOpen(TTY, 9600);

	if (uart0_fd == -1)
	{
		printf("ERROR - can't open UART port");

		return -1;
	}

	if (wiringPiSetup() == -1)
	{
		printf("ERROR - wiringPiSetup failed");

		return -1;
	}

	puts(TTY " connected.");
	puts("UART ready:");
	system("stty -F " TTY);
	puts("");

	serialFlush(uart0_fd);

    int index = 0;
    int raw[VECTOR_LENGTH] = {0};

    while (1)
    {
        raw[index] = get_raw();

        if (index == VECTOR_LENGTH - 1)
            average(raw);

        index = (index + 1) % VECTOR_LENGTH;
    }

    return 0;
}