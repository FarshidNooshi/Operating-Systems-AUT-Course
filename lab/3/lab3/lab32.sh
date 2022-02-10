#!/bin/bash	

for input in $1 $2
do
	if ! [[ "$input" =~ ^[0-9]+$ ]] ; 
	 then exec >&2; echo "error: Not a number, please enter two valid numbers"; exit 1
	fi

done
let summ=$1+$2
echo "sum is $summ"


if [ "$1" -gt "$2" ]
then
 echo "$1 is greater than the second number"
else
 echo "$2 is greater than or equal the first number"
fi



