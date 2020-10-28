#!/bin/bash

echo "Conecte um LED+resistor ao GPIO 4"

echo "Pinos GPIO disponiveis:"
ls -l /sys/class/gpio

echo "Criando conexao ao GPIO 4 via sysfs"
sudo echo "4" >> /sys/class/gpio/export
echo "Confira o diretorio GPIO4 criado..."
ls -l /sys/class/gpio

echo "Acendendo o LED"
sudo echo "out" > /sys/class/gpio/gpio4/direction
sudo echo "1" > /sys/class/gpio/gpio4/value

echo "Delay de 5s"
sleep 5

echo "Apagando o LED"
sudo echo "0" > /sys/class/gpio/gpio4/value

echo "Liberando o GPIO 4"
sudo echo "4" >> /sys/class/gpio/unexport
echo "Confira o diretorio GPIO4 apagado..."
ls -l /sys/class/gpio

echo "FIM"