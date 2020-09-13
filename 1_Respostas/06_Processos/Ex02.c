#include <stdio.h>
#include <stdlib.h>

// Define a quantidade de processos filhos gerados
#define QNT_PROCESS 3
#define COUNTER (QNT_PROCESS - 1)

int main(int argc, char **argv)
{
  int counter = 1;

  if (argc > 1)
  {
    int ret;

    while (counter < argc)
      ret = system(argv[counter++]);
  }
  else
    printf("Entre com algum argumento (**argv)\n");

  return 0;

}
