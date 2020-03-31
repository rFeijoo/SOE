#include <stdio.h>

int main(int argc, char **argv)
{
  int aux = 1;

  if (argc > 1)
  {
    printf("Argumentos: ");
    while (aux < argc)
      printf("%s ", argv[aux++]);
    printf("\n");
  }
  else
    printf("Entre com algum argumento (**argv)\n");

  return 0;
}
