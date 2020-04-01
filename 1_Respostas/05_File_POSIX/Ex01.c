#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  char texto[10] = "Ola mundo!";

  int fp = open("ola_mundo.txt", O_RDWR | O_CREAT, S_IRWXU);

  if (fp == -1)
  {
    printf("Erro na abertura do arquivo.\n");
    return -1;
  }

  for (int i=0; i<10; i++)
    write(fp, &(texto[i]), 1);
  write(fp, "\n", 1);

  printf("Arquivo aberto com sucesso!\n");

  close(fp);

  return 0;
}
