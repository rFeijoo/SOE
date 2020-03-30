#include <stdio.h>

int main(int argc, char **argv)
{
  if (argc > 1)
    printf("Ola %s!\n", argv[1]);
  else
    printf("Entre com algum argumento (**argv)\n");

  return 0;
}
