#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SAIDA 7 // GPIO 4

void sqwv(int pin, int degree, int N)
{
	int t1 = (50 * degree + 4) / 9 + 1500;
	int t2 = 20000 - t1;
	int i;

	for (i=0; i<N; i++)
	{
		digitalWrite(pin, HIGH);
		usleep(t1);
		digitalWrite(pin, LOW);
		usleep(t2);
	}
}

int main(int argc, char *argv[])
{
	int d = 0, t = 50;

	if (argc > 2)
	{
		d = atoi(argv[1]);
		
        if (d < -90)
			d = -90;
		else if (d > 90)
			d = 90;

		t = atoi(argv[2]);

		if (t < 0)
			t = 1;
	}

	wiringPiSetup();

	pinMode(SAIDA, OUTPUT);

	sqwv(SAIDA, d, t);

	return 0;
}