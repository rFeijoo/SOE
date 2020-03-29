#!/bin/bash

input="sites.txt"
while IFS= read -r line
do
  cmd="wget $line"
  echo `$cmd`
done < "$input"
