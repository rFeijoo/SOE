#include <stdio.h>

int main(int argc, char **argv)
{
  FILE *fp;

  char texto[10] = {'O','l','a',' ','m','u','n','d','o','!'};

  fp = fopen("ola_mundo.txt", "w");

  if (fp == NULL)
  {
    printf("Erro na abertura do arquivo.\n");
    return -1;
  }

  for (int i=0; i<10; i++)
    putc(texto[i], fp);
  putc('\n', fp);

  printf("Arquivo aberto com sucesso!\n");

  fclose(fp);

  return 0;
}
