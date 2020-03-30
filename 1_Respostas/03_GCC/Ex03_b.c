#include <stdio.h>

int main(int argc, char **argv)
{
  int i, counter;
  char nome[50], c = 'a';

  printf("Digite o seu nome: ");

  i = 0;
  while (counter < 2)
  {
    scanf("%c", &c);

    if (c == '"')
      counter++;
    else
      nome[i++] = c;
  }
  nome[i] = '\0';

  printf("Olá %s!\n", nome);

  return 0;
}
