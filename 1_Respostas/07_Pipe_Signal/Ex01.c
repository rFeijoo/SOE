#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
  int pid, fd[2];

  printf("Main process [%d]\n", (int)getpid());

  pipe(fd);

  pid = fork();

  printf("End process [%d]\n", (int)getpid());

  return 0;
}
