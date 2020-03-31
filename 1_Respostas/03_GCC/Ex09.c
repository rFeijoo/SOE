#include <stdio.h>
#include "num_caracs.h"

int main(int argc, char **argv)
{
  int length, aux = 0;

  while (aux < argc)
  {
    length = Num_Caracs(argv[aux]);
    printf("Argumento: %s / Numero de caracteres: %d\n", argv[aux++], length);
  }

  return 0;
}
