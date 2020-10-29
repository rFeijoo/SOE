#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "gpio_sysfs.h"

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

void parent_process(int *fd)
{
  int state;
  char msg[30];

  int last_freq, freq = 500000;

  signal(SIGINT, unset_GPIO);

  if (setGPIOdirection(btn_pin, "in") < 0)
  {
    printf("ERROR - unable to set GPIO %d\n", btn_pin);
      
    unset_GPIO(0);
  }

  last_freq = freq;

  for (;;)
  {
    if (GPIOread(btn_pin))
    {
      freq /= 2;

      sleep(1); // debounce
    }

    if (freq < 7812)
      freq = 500000;

    if (freq != last_freq)
    {
      sprintf(msg, "%d", freq);

      if (write(fd[1], msg, sizeof(msg)) < 0)
      {
        printf("ERROR - failed to send message to son\n");

        unset_GPIO(0);
      }

      last_freq = freq;
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