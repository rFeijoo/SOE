#include <stdio.h>
#include <string.h>
#include "bib_arqs.h"

int findFile(char *file)
{
  int fp = open(file, O_RDONLY);

  if (fp == -1)
    return 0;

  return 1;
}

int findWord(char *word, char *str)
{
  int length  = 0;
  int matches = 0;

  for (int i=0; word[i]!='\0'; i++)
    length++;

  char aux[length + 1];

  for (int i=0; str[i]!='\0'; i++)
  {
    if (str[i] == word[0])
    {
      for (int j=0; j<length; j++)
        aux[j] = str[i + j];
      aux[length] = '\0';

      if (strcmp(word, aux) == 0)
        matches++;
    }
  }

  return matches;
}

int main(int argc, char **argv)
{
  char *ptr;
  int index, counter = 0;
  int fileOpened[argc];

  // Input validation
  if (argc < 3)
  {
    printf("Entre com UMA palavra e, pelo menos, um arquivo \".txt\". [**argv]\n");
    return -1;
  }

  // Verify which file exists
  index = 2;
  while (index < argc)
  {
    fileOpened[index] = findFile(argv[index]);
    if (fileOpened[index] == 1)
      fileOpened[0] = 1;
    index++;
  }

  // Find words in each file
  index = 2;
  while (index < argc)
  {
    if (fileOpened[index] == 1)
    {
      ptr = le_arq_texto(argv[index]);
      counter += findWord(argv[1], ptr);
      free(ptr);
    }
    index++;
  }

  // Print result
  if (fileOpened[0] == 1)
  {
    printf("\'%s\' ocorre %d vez(es) no(s) arquivo(s) ", argv[1], counter);
    for (int i=2; i<argc; i++)
    {
      if (i > 2 && fileOpened[i] == 1)
        printf(", ");
      if (fileOpened[i] == 1)
        printf("\'%s\'", argv[i]);
    }
    printf(".\n");
    // Untracked files
    for (int i=2; i<argc; i++)
    {
      if (fileOpened[i] == 0)
        printf("Arquivo \'%s\' não encontrado.\n", argv[i]);
    }
  }
  else
    printf("ERRO - falha na abertura do(s) arquivo(s).\n");

  return 0;
}
