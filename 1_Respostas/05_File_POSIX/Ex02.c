#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
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

void writeFile(int fp, char *name, int age)
{
  char str1[30]  = "";
  char str2[30]  = "";
  char auxAge[5] = "";

  concatName("Nome: ", name, str1);

  sprintf(auxAge, "%d", age);
  concatName("Idade: ", auxAge, str2);
  concatName(" ", "anos", str2);

  for (int i=0; str1[i]!='\0'; i++)
    write(fp, &(str1[i]), 1);
  write(fp, "\n", 1);

  for (int i=0; str2[i]!='\0'; i++)
    write(fp, &(str2[i]), 1);
  write(fp, "\n", 1);
}

int main(int argc, char **argv)
{
  char name[20] = "";
  int  age;

  printf("Digite o seu nome: ");
  scanf("%19s", name);
  printf("Digite a sua idade: ");
  scanf("%d", &age);

  char fn[25] = "";
  concatName(name, ".txt", fn);

  int fp = open(fn, O_RDWR | O_CREAT, S_IRWXU);

  if (fp == -1)
  {
    printf("Erro na abertura do arquivo.\n");
    return -1;
  }

  writeFile(fp, name, age);

  printf("Arquivo aberto com sucesso!\n");

  close(fp);

  return 0;
}
