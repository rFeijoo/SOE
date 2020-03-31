#include "num_caracs.h"

int Num_Caracs(char *string)
{
  int i = 0;

  while (string[i] != '\0' && string[i] != '\n')
    i++;

  return i;
}
