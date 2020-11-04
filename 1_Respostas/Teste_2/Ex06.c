#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define TTY "/dev/ttyS0"

int main(void)
{
	int user_choice;
	int user_input;
	unsigned char msp_ans;
	int fd;

	wiringPiSetup();

	fd = serialOpen(TTY, 9600);

	puts(TTY " aberto.");
	puts("UART configurada:");

	system("stty -F " TTY);
	puts("");
	serialFlush(fd);

	puts("MICRO BATALHA NAVAL...");

	do {
		puts("Escolha um valor entre 0 e 255.");
		scanf("%d", &user_choice);
	} while ((user_choice<0)||(user_choice>255));

	while (1)
	{
		puts("Tente adivinhar o numero entre 0 e 255 "
			"escolhido pelo MSP430:");

		scanf("%d", &user_input);

		serialPutchar(fd, (unsigned char)user_input);

		msp_ans = serialGetchar(fd);

		if (msp_ans > 0)
		{
			puts("Parabens! Voce venceu!");

			serialClose(fd);

			return 0;
		}
		else
			puts("Voce errou.");

		msp_ans = serialGetchar(fd);

		printf("O valor adivinhado pelo MSP430"
				" foi %d.\n", msp_ans);

		if (msp_ans == user_choice)
		{
			serialPutchar(fd, 1);

			puts("Infelizmente voce perdeu...");

			serialClose(fd);

			return 0;
		}
		else
		{
			serialPutchar(fd, 0);

			puts("Ufa! Ele errou.");
		}
	}
	serialClose(fd);
    
	return 0;
}