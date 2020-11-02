#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>

#define VECTOR_LENGTH 100

int spi_fd;

unsigned int get_raw(void)
{
    unsigned char send_msp430[3];
    unsigned int  result = 0;

    // Request A/D conversion MSP430
    send_msp430[0] = 0x55;

    wiringPiSPIDataRW(0, &send_msp430[0], 1);

    if (send_msp430[0] == 0xAA)
    {
        usleep(100);

        send_msp430[1] = 0x1;
        send_msp430[2] = 0x2;

        wiringPiSPIDataRW(0, &send_msp430[1], 1);
        wiringPiSPIDataRW(0, &send_msp430[2], 1);

        result += ((unsigned int)send_msp430[1]) + ((unsigned int)send_msp430[2] << 8);
    }

    return result;
}

void average(unsigned int *ptr)
{
    float voltage, av = 0;

    for (int i=0; i<VECTOR_LENGTH; i++)
        av += (float)ptr[i] / VECTOR_LENGTH;

    voltage = av * (3.3 / 1024);

    printf("MSP430 A/D Voltage average = %.2f\n", voltage);
}

void ctrl_c(int sig)
{
	close(spi_fd);

	exit(0);
}

int main(void)
{
	signal(SIGINT, ctrl_c);

	if (wiringPiSetup() == -1)
	{
		printf("ERROR - wiringPiSetup failed");
		return -1;
	}

	spi_fd = wiringPiSPISetup(0, 500000);

	if (spi_fd == -1)
	{
		printf("ERROR - can't open SPI port");
		return -1;
	}

    int index = 0;
    unsigned int raw[VECTOR_LENGTH] = {0};

    while (1)
    {
        raw[index] = get_raw();

        if (index == VECTOR_LENGTH - 1)
            average(raw);

        index = (index + 1) % VECTOR_LENGTH;

        usleep(10000);
    }
}
