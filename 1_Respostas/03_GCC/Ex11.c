#include <stdio.h>
#include "num_caracs.h"

int main(int argc, char **argv)
{
  int length, aux = 0;

  length = 0;
  while (aux < argc)
    length += Num_Caracs(argv[aux++]);
  printf("Total de caracteres de entrada: %d\n", length);

  return 0;
}
