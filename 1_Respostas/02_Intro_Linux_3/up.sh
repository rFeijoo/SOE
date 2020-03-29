#!/bin/bash

# DICA: use ". ./up.sh 2", para voltar 2 diretórios
echo "DICA: use \". ./up.sh 2\", para voltar 2 diretórios"
i=1
while [ $i -le $1 ]
do
  cd ".."
  i=$((i+1))
done
