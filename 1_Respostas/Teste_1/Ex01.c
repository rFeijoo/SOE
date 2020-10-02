#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  for (int i=1; i<argc; i++)
  {
    if (fork()==0)
    {
      system(argv[i]);

      exit(0);
    }
    else
      wait(NULL);
  }
  return 0;
}
