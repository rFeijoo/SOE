#!/bin/bash

#./cals.sh MES1 ANO1 MES2 ANO2 MES3 ANO3

while [ ! -z $1 ]
do
  texto="cal -m $1 $2"
  echo `$texto`
  shift
  shift
done
