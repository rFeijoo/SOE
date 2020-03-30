#include <stdio.h>

int main(int argc, char **argv)
{
  char nome[15];

  printf("Digite o seu nome: ");

  scanf("%s", nome);

  printf("Olá %s!\n", nome);

  return 0;
}
