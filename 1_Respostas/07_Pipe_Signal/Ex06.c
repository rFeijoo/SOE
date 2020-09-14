#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 128
#define QNT_CHILD   2

void write_pipe(int buf, char *str)
{
  int state;

  if (write(buf, str, BUFFER_SIZE) < 0)
  {
    printf("Erro na escrita da mensagem\n");
    wait(&state);
  }

  sleep(1);
}

void read_pipe(int buf)
{
  char str[BUFFER_SIZE];

  if (read(buf, str, BUFFER_SIZE) < 0)
    printf("Erro na leitura da mensagem\n");
  else
    printf("Mensagem recebida [PID = %d] = %s\n", (int)getpid(), str);

  sleep(1);
}

int register_parent(void)
{
  int pid = (int)getpid();

  printf("Processo pai [PID = %d]\n", pid);

  return pid;
}

void son1_routine(int *fd)
{
  printf("Processo filho 1 [PID = %d]\n", (int)getpid());

  write_pipe(fd[1], "Quando o vento passa, é a bandeira que se move.");

  sleep(2);

  read_pipe(fd[0]);
}

void son2_routine(int *fd)
{
  printf("Processo filho 2 [PID = %d]\n\n", (int)getpid());

  read_pipe(fd[0]);

  write_pipe(fd[1], "Não, é o vento que se move.");
}

void register_son(int parent, int *fd)
{
  int pid = fork();

  if (pid == 0)
  {
    int son = (int)getpid() - parent;

    if (son == 1)
      son1_routine(fd);
    else
      son2_routine(fd);
  }
  else
    return;

  exit(1);
}

int main(int argc, char **argv)
{
	int pid_parent;
  int fd[2];

  pipe(fd);

  pid_parent = register_parent();

  for (int i=0; i<QNT_CHILD; i++)
    register_son(pid_parent, fd);

  // Rotina do processo pai
  sleep(3);

  read_pipe(fd[0]);

  write_pipe(fd[1], "Os dois se enganam. É a mente dos senhores que se move.");

  return 0;
}
