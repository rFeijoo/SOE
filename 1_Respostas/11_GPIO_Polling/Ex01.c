#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "gpio_sysfs.h"
#include <sys/poll.h>

#define N 1000
#define Nlim (N*3)/4

const int led_pin = 4;
const int btn_pin = 17;

int son_pid;

void unset_GPIO(int signum)
{
  kill(son_pid, SIGINT);
  fprintf(stderr, "\nSon process killed.\n");

  unsetGPIO(led_pin);
  fprintf(stderr, "LED GPIO free\n");

  unsetGPIO(btn_pin);
  fprintf(stderr, "BTN GPIO free\n");

  exit(0);
}

void poll_btn(struct pollfd *pfd)
{
	char buffer, vals[N] = {0};
	int pos = 0, test=1, i, s;
	lseek(pfd->fd, 0, SEEK_SET);
	read(pfd->fd, &buffer, 1);
	for(i=0;i<N;i++) vals[i] = buffer-'0';
	poll(pfd, 1, -1);
	while(test)
	{
		lseek(pfd->fd, 0, SEEK_SET);
		read(pfd->fd, vals+pos, 1);
		vals[pos] -= '0';
		pos = (pos+1)%N;
		for(s=i=0; i<N; i++)
			s += vals[i];
		if(buffer=='0')
			test = s<Nlim;
		else
			test = s>Nlim;
	}
}

void parent_process(int *fd)
{
  int state;
  char msg[30], buffer[50];
  struct pollfd pfd;

  int freq = 500000;

  signal(SIGINT, unset_GPIO);

  if (setGPIOdirection(btn_pin, "in") < 0)
  {
    printf("ERROR - unable to set GPIO %d\n", btn_pin);
      
    unset_GPIO(0);
  }

  sprintf(buffer, "echo both > /sys/class/gpio/gpio%d/edge", btn_pin);
  system(buffer);

  sprintf(buffer, "/sys/class/gpio/gpio%d/value", btn_pin);
  pfd.fd = open(buffer, O_RDONLY);
  if (pfd.fd < 0)
  {
    printf("ERRO - can't open \'/sys/class/gpio\'\n");

    unset_GPIO(0);
  }

  pfd.events = POLLPRI | POLLERR;
  pfd.revents = 0;

  for (;;)
  {
    // Button pressed
    poll_btn(&pfd);

    // Button released
    poll_btn(&pfd);

    freq /= 2;

    if (freq < 7812)
      freq = 500000;

    sprintf(msg, "%d", freq);

    if (write(fd[1], msg, sizeof(msg)) < 0)
    {
      printf("ERROR - failed to send message to son\n");

      unset_GPIO(0);
    }
  }
}

void son_process(int *fd)
{
  char msg[30];
  int n = 0;

  int freq = 500000;

  if (setGPIOdirection(led_pin, "out") < 0)
  {
    printf("ERROR - unable to set GPIO %d\n", led_pin);
      
    kill(getppid(), SIGINT);
  }

  for (;;)
  {
    if (read(fd[0], msg, 30) > 0)
      freq = atoi(msg);

    GPIOwrite(led_pin, 1);

    usleep(freq);

    GPIOwrite(led_pin, 0);

    usleep(freq);
  }
}

int main(int argc, char **argv)
{
  int fd[2];

  printf("Processo principal [PID = %d]\n", (int)getpid());

  pipe(fd);

  if (fcntl(fd[0], F_SETFL, O_NONBLOCK) < 0) 
    exit(1);

  son_pid = fork();

  if (son_pid == 0)
    son_process(fd);
  else
    parent_process(fd);

  return 0;
}