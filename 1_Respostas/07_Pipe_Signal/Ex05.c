#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 128

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

int main(int argc, char **argv)
{
	int pid, fd[2];

	pipe(fd);

	pid = fork();

	if (pid == 0) // Processo do filho
	{
    printf("Processo filho [PID = %d]\n", (int)getpid());

    write_pipe(fd[1], "Pai, qual é a verdadeira essência da sabedoria?");

    read_pipe(fd[0]);

    write_pipe(fd[1], "Mas até uma criança de três anos sabe disso!");

    read_pipe(fd[0]);
	}
	else // Processo do pai
	{
    printf("Processo pai [PID = %d]\n", (int)getpid());

    read_pipe(fd[0]);

    write_pipe(fd[1], "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");

    read_pipe(fd[0]);

    write_pipe(fd[1], "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
	}

  return 0;
}
