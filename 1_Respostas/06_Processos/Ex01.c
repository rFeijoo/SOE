#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Define a quantidade de processos filhos gerados
#define QNT_PROCESS 3
#define COUNTER (QNT_PROCESS - 1)

int main(int argc, char **argv)
{
  pid_t parent_pid = getpid();
  pid_t child_pid[COUNTER];

  printf("PID do processo pai: %d\n", (int)parent_pid);

  for (int i=0; i<COUNTER; i++)
    child_pid[i] = fork();

  if ((int)getpid() - (int)parent_pid > 0)
    printf("PID do processo filho: %d\n", (int)getpid());

  return 0;
}
