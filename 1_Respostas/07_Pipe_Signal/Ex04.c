#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void parent_process(int *fd)
{
  int state;
  char msg[30];

  for (int i=1; i<=10; i++)
  {
    sprintf(msg, "%d", i);

    if (write(fd[1], msg, sizeof(msg)) < 0)
    {
      printf("Erro na escrita da mensagem\n");
      wait(&state);
    }

    sleep(1);
  }

  printf("Fim de execução do processo pai [PID = %d]\n", (int)getpid());

  exit(1);

}

void son_process(int *fd)
{
  char msg[30];
  int n = 0;

  while (n != 10)
  {
    if (read(fd[0], msg, 30) < 0)
      printf("Erro na leitura da mensagem\n");
    else
      printf("Mensagem recebida [PID = %d] = %s\n", (int)getpid(), msg);

    n = atoi(msg);
  }

  printf("Fim de execução do processo filho [PID = %d]\n", (int)getpid());

  exit(1);
}

int main(int argc, char **argv)
{
  int pid, fd[2];

  printf("Processo principal [PID = %d]\n", (int)getpid());

  pipe(fd);

  pid = fork();

  if (pid == 0)
    son_process(fd);
  else
    parent_process(fd);

  return 0;
}
