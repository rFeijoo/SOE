#!/bin/bash

criar_arquivos()
{
  echo "Criando arquivos \"teste.txt\"..."
  for i in {1..100}
  do
    name="teste$i.txt"
    touch $name
    texto="Número do arquivo = $i"
    echo $texto > $name
  done
}

apagar_arquivos()
{
  echo "Apagando arquivos \"teste.txt\"..."
  rm -r teste*.txt
  echo "Arquivos apagados"
}

echo "Escolha uma opção:"
echo "1 - Criar arquivos"
echo "2 - Apagar a lixeira"
read opcao
if [ $opcao -eq 1 ]; then
  criar_arquivos
elif [ $opcao -eq 2 ]; then
  apagar_arquivos
else
  echo "ERRO - Opção inválida!"
fi
