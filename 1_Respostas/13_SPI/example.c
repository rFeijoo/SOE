#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>

int spi_fd;

void ctrl_c(int sig)
{
	close(spi_fd);

	exit(0);
}

int main(void)
{
	unsigned char send_msp430, user_input = 1;

	signal(SIGINT, ctrl_c);

	if (wiringPiSetup() == -1)
	{
		printf("ERROR - wiringPiSetup failed");
		return -1;
	}

	spi_fd = wiringPiSPISetup (0, 500000);

	if (spi_fd == -1)
	{
		printf("ERROR - can't open SPI port");
		return -1;
	}

	while (user_input != 0)
	{
    	printf("Type a number between 1 and 5 to blink, or 0 to exit\n");

		scanf("%d", &user_input);

		if ((user_input < 0) || (user_input > 5))
			puts("ERROR - invalid value");
		else if (user_input > 0)
		{
			send_msp430 = user_input;

			wiringPiSPIDataRW(0, &send_msp430, 1);

			printf("MSP430_return = %d\n", send_msp430);
      
			sleep(1+user_input/2);
		}
		puts("");
	}
	close(spi_fd);
}
