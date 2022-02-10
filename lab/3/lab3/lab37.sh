#!/bin/bash	


echo "firstnumber, secondnumber, operator(+-./)" 
read -ra array

arraylength=${#array[@]}

case ${array[2]} in 
  +)
	summ=$(echo "scale=4; ${array[0]} + ${array[1]}" | bc)
	printf "sum is "	
	printf %.10f\\n $summ
	;;
  -)
	summ=$(echo "scale=4; ${array[0]} - ${array[1]}" | bc)
	printf "difference is "	
	printf %.10f\\n $summ
	;;
  .)
	summ=$(echo "scale=4; ${array[0]} * ${array[1]}" | bc)
	printf "product is "	
	printf %.10f\\n $summ
	;;
  /)
	summ=$(echo "scale=4; ${array[0]} / ${array[1]}" | bc)
	printf "ratio is "	
	printf %.10f\\n $summ
	;;
  *)
	echo "invalid operation"
	;;

esac
