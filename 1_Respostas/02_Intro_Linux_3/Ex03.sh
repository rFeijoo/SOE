#!/bin/bash

echo "Entre com o mês do seu aniversário"
read mes
for i in {2019..2009}
do
  texto="cal -m $mes $i"
  echo `$texto`
done
