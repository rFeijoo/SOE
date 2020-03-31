#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void concatName(char *n1, char *n2, char *n3)
{
  int index = 0;

  for (int i=0; n3[i]!='\0'; i++)
    index++;

  for (int i=0; n1[i]!='\0'; i++)
    n3[index++] = n1[i];

  for (int i=0; n2[i]!='\0'; i++)
    n3[index++] = n2[i];

  n3[index] = '\0';
}

void writeFile(FILE *fp, char *name, char *age)
{
  char str1[30]  = "";
  char str2[30]  = "";

  concatName("Nome: ", name, str1);

  concatName("Idade: ", age, str2);
  concatName(" ", "anos", str2);

  for (int i=0; str1[i]!='\0'; i++)
    putc(str1[i], fp);
  putc('\n', fp);

  for (int i=0; str2[i]!='\0'; i++)
    putc(str2[i], fp);
  putc('\n', fp);
}

int main(int argc, char **argv)
{
  FILE *fp;

  if (argc != 3)
  {
    printf("Entre com seu nome e idade, respectivamente. [**argv]\n");
    return -1;
  }

  char fn[25] = "";
  concatName(argv[1], ".txt", fn);

  fp = fopen(fn, "w");

  if (fp == NULL)
  {
    printf("Erro na abertura do arquivo.\n");
    return -1;
  }

  writeFile(fp, argv[1], argv[2]);

  printf("Arquivo aberto com sucesso!\n");

  fclose(fp);

  return 0;
}
