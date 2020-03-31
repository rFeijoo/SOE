#include <stdio.h>
#include "bib_arqs.h"

int main(int argc, char **argv)
{
  char *str;
  int counter = 1;

  if (argc < 2)
  {
    printf("Entre com o nome de, pelo menos, um arquivo \".txt\". [**argv]\n");
    return -1;
  }

  while (counter < argc)
  {
    str = le_arq_texto(argv[counter]);

    printf("%s", str);

    free (str);
    
    counter++;
  }

  return 0;
}
