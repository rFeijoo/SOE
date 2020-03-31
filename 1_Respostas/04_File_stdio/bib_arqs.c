#include "bib_arqs.h"

int tam_arq_texto(char *nome_arquivo)
{
  FILE *fp;
  int counter = 0;

  fp = fopen(nome_arquivo, "r");

  if (fp == NULL)
  {
    printf("Erro na abertura do arquivo.\n");
    return -1;
  }

  char c = getc(fp);
  while(c != EOF)
  {
    c = getc(fp);
    counter++;
  }

  fclose(fp);

  return counter;
}

char *le_arq_texto(char *nome_arquivo)
{
  FILE *fp;
  char *str;
  int  i = 0;

  int length = tam_arq_texto(nome_arquivo);

  str = (char *) malloc(length + 1);

  fp = fopen(nome_arquivo, "r");

  if (fp == NULL)
  {
    printf("Erro na abertura do arquivo.\n");
    return NULL;
  }

  char c = getc(fp);
  while(c != EOF)
  {
    str[i++] = c;
    c = getc(fp);
  }
  str[i] = '\0';

  fclose(fp);

  // free (str);

  return str;
}
