#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
  int pid, fd[2], state;
  char msg[30];

  printf("Main process [PID = %d]\n", (int)getpid());

  if (pipe(fd) < 0)
  {
    printf("ERROR - unable to create pipe\n");
    exit(1);
  }
  else if ((pid = fork()) < 0)
  {
    printf("ERROR - unable to create process\n");
    exit(1);
  }
  else if (pid == 0)
  {
    if (read(fd[0], msg, 30) < 0)
      printf("ERROR - unable to read message\n");
    else
      printf("MESSAGE = %s\n", msg);
  }

  strcpy(msg, "message from parent to child");

  if (write(fd[1], msg, sizeof(msg)) < 0)
  {
    printf("ERROR - unable to write message\n");
    wait(&state);
  }

  printf("End process [PID = %d]\n", (int)getpid());

  return 0;
}
