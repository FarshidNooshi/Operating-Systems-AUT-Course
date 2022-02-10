#!/bin/bash	

x=$1
y=$2
filename=$3
counter=1

#printing lines x, x+1, ..., y from filename

cat $filename | while read LINE; do
    if [ $counter -ge $x ] && [ $counter -le $y ]; 
     then echo $LINE
    fi
    counter=$(($counter + 1))
done



