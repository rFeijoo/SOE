#include "bib_arqs.h"

int tam_arq_texto(char *nome_arquivo)
{
  char c;
  int counter = 0;

  int fp = open(nome_arquivo, O_RDONLY);

  if (fp == -1)
  {
    printf("Erro na abertura do arquivo.\n");
    return -1;
  }

  while(read(fp, &c, 1) != 0)
    counter++;

  close(fp);

  return counter;
}

char *le_arq_texto(char *nome_arquivo)
{
  char *str, c;
  int  i = 0;

  int length = tam_arq_texto(nome_arquivo);

  str = (char *) malloc(length + 1);

  int fp = open(nome_arquivo, O_RDONLY);

  if (fp == -1)
  {
    printf("Erro na abertura do arquivo.\n");
    return NULL;
  }

  while(read(fp, &c, 1) != 0)
    str[i++] = c;
  str[i] = '\0';

  close(fp);

  // free (str);

  return str;
}
