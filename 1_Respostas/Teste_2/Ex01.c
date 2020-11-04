#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wiringPi.h>

#define N 1000
#define Nlim (N*3)/4

const int led_pin = 7;  // GPIO 4
const int btn_pin = 0;  // GPIO 17

int son_pid;

void unset_GPIO(int signum)
{
  kill(son_pid, SIGINT);
  fprintf(stderr, "\nSon process killed.\n");

  digitalWrite(led_pin, LOW);

  exit(0);
}

void parent_process(int *fd)
{
  int state;
  char msg[30], buffer[50];

  int duty[5] = {0, 25, 50, 75, 100};
  int index = 0;

  signal(SIGINT, unset_GPIO);

  for (;;)
  {
    if (digitalRead(btn_pin) == HIGH)
    {
      index = (index + 1) % 5;

      sprintf(msg, "%d", duty[index]);

      if (write(fd[1], msg, sizeof(msg)) < 0)
      {
        printf("ERROR - failed to send message to son\n");

        unset_GPIO(0);
      }

      delay(800);
    }
  }
}

void son_process(int *fd)
{
  char msg[30];
  int n = 0;

  int last_duty, duty = 0;

  int t_on  = 0;
  int t_off = 20;

  last_duty = duty;

  for (;;)
  {
    if (read(fd[0], msg, 30) > 0)
      duty = atoi(msg);

    if (last_duty != duty)
    {
      t_on  = (t_on + 5) % 25;
      t_off = 20 - t_on;

      last_duty = duty;
    }

    digitalWrite(led_pin, HIGH);

    delay(t_on);

    digitalWrite(led_pin, LOW);

    delay(t_off);
  }
}

int main(int argc, char **argv)
{
  int fd[2];

  pipe(fd);

  if (fcntl(fd[0], F_SETFL, O_NONBLOCK) < 0) 
    exit(1);

  wiringPiSetup();

  pinMode(btn_pin, INPUT);
  pinMode(led_pin, OUTPUT);

  son_pid = fork();

  if (son_pid == 0)
    son_process(fd);
  else
    parent_process(fd);

  return 0;
}