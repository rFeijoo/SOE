#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

#define N 100
#define Nlim N/2

#define GPIO_N "4"

#define GPIO_EXP "/sys/class/gpio/export"
#define GPIO_UNX "/sys/class/gpio/unexport"
#define GPIO_FLD "/sys/class/gpio/gpio" GPIO_N
#define GPIO_EDG GPIO_FLD "/edge"
#define GPIO_DIR GPIO_FLD "/direction"
#define GPIO_VAL GPIO_FLD "/value"

void poll_btn(struct pollfd *pfd)
{
	char buffer, vals[N] = {0};
	int pos = 0, test=1, i, s;

	lseek(pfd->fd, 0, SEEK_SET);

	read(pfd->fd, &buffer, 1);

	for (i=0;i<N;i++)
		vals[i] = buffer-'0';

	poll(pfd, 1, -1);

	while (test)
	{
		lseek(pfd->fd, 0, SEEK_SET);

		read(pfd->fd, vals+pos, 1);

		vals[pos] -= '0';
		pos = (pos + 1) % N;

		for (s=i=0; i<N; i++)
			s += vals[i];

		if (buffer == '0')
			test = s<Nlim;
		else
			test = s>Nlim;
	}
}

int main(void)
{
	struct pollfd pfd;
	int btn_press;

	system("echo " GPIO_N " > " GPIO_EXP);
	system("echo both > " GPIO_EDG);
	system("echo in > " GPIO_DIR);

	pfd.fd = open(GPIO_VAL, O_RDONLY);

	if (pfd.fd < 0)
	{
		puts("Erro abrindo " GPIO_VAL ".");
		puts("Execute este programa como root.");
		return 1;
	}

	pfd.events = POLLPRI | POLLERR;
	pfd.revents = 0;

	puts("Pressione o botao...");

	for (btn_press=0; btn_press<5; btn_press++)
	{
		poll_btn(&pfd);
		puts("Borda de descida!");
		poll_btn(&pfd);
		puts("Borda de subida!");
	}

	close(pfd.fd);

	system("echo 4 > " GPIO_UNX);

	return 0;
}