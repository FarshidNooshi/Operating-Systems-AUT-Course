#!/bin/bash	


echo "firstnumber, secondnumber, operator(+-./)" 
read -ra array

arraylength=${#array[@]}

for ((i=0; i<${arraylength} - 1; i++))
do
	input=${array[$i]}
	if ! [[ "$input" =~ ^[0-9]+$ ]] ; 
	 then exec >&2; echo "error: Not a number, please enter two valid numbers"; exit 1
	fi

done

case ${array[2]} in 
  +)
	let summ=${array[0]}+${array[1]}
	echo "sum is $summ"
	;;
  -)
	let summ=${array[0]}-${array[1]}
	echo "difference is $summ"
	;;
  .)
	let summ=${array[0]}\*${array[1]}
	echo "product is $summ"
	;;
  /)
	let summ=${array[0]}/${array[1]}
	echo "ratio is $summ"
	;;
  *)
	echo "invalid operation"
	;;

esac
