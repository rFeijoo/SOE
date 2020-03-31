#include <stdio.h>

int main(int argc, char **argv)
{
  int i;
  char nome[30], c = 'a';

  printf("Digite o seu nome: ");

  i = 0;
  while (c != '\0' && c != '\n')
  {
    scanf("%c", &c);
    nome[i++] = c;
  }
  nome[--i] = '\0';

  printf("Olá %s!\n", nome);

  return 0;
}
