#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int spawn(char *str)
{
  pid_t child_pid = fork();

  if (child_pid != 0)
    return (int)child_pid;
  else
  {
    char *args[] = {str, NULL};

    execvp(args[0], args);

    fprintf(stderr, "ERROR\n");

    abort();
  }
}

int main(int argc, char **argv)
{
  int pid = 0, counter = 1;

  if (argc > 1)
  {
    printf("PID do processo principal: %d\n", (int)getpid());

    while (counter < argc)
    {
      pid = spawn(argv[counter++]);

      printf("Fim de execução [PID = %d]\n", pid);

      sleep(1);
    }
  }
  else
    printf("Entre com algum argumento (**argv)\n");

  printf("Fim de execução [PID = %d]\n", (int)getpid());

  return 0;
}
