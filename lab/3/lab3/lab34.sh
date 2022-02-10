#!/bin/bash    


while [ 1 = 1 ]
do

 read -p 'please enter a number: ' number
 len=`expr length "$number"`
 for ((i= $len - 1;i>=0;i--))
  do
    reverse="$reverse${number:$i:1}"
  done
  echo "the reverse is: $reverse"
  reverse=""
done

