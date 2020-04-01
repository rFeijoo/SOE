#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef _BIB_ARQS_H
  #define _BIB_ARQS_H

  int  tam_arq_texto(char *nome_arquivo);
  char *le_arq_texto(char *nome_arquivo);

#endif /*_BIB_ARQS_H*/
