#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>

#define N 1000
#define M 50

int sample = 0, d[N], ms = 0;
int fd;
double m;

void loop(int sig)
{
	unsigned char txrx;

	do {
		txrx = 0xA5;
		wiringPiSPIDataRW(0, &txrx, 1);
	} while (txrx != 0x5A);

	usleep(100);

	txrx = 1;
	wiringPiSPIDataRW(0, &txrx, 1);
	d[sample] = (unsigned int)txrx;

	txrx = 2;
	wiringPiSPIDataRW(0, &txrx, 1);
	d[sample] += ((unsigned int)txrx)<<8;

	m += (double)d[sample];
    
	sample = (sample + 1) % N;

	if (sample == 0)
	{
		printf("Valor medio = %f V\n", m*3.3/1023.0/N);

		ms++;

		m = 0.0;
	}

	if (ms == M)
	{
		close(fd);

		exit(0);
	}
}

int main(void)
{
	wiringPiSetup();

	fd = wiringPiSPISetup (0, 500000);

	signal(SIGALRM, loop);

	ualarm(1, 500);

	while(1)
        ;

    return 0;
}