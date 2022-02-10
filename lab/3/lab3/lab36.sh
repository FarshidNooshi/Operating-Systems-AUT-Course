#!/bin/bash	

function type1(){
 for((i=1;i<=5;i++)) do
  val=""
  for((j=1;j<=i;j++)) do
   val=($val$i)
  done
  echo $val
 done
}


function type2(){
 val="|_"
 val2="| "
 for((i=0;i<5;i++)) do
   res=""
	for((j=0;j<5-i;j++)) do
           printf " "
          done
	  for((j=5 - $i;j<=5 + $i;j = $j + 2)) do
	   printf ". "
	  done
	  echo ""
 done
 for((i=4;i>=0;i--)) do
   res=""
	for((j=0;j<5-i;j++)) do
           printf " "
          done
	  for((j=5 - $i;j<=5 + $i;j = $j + 2)) do
	   printf ". "
	  done
	  echo ""
 done
}

function type3(){
 val="|_"
 val2="| "
 for((i=0;i<5;i++)) do
   res=""
	  for((j=0;j<$i ;j++)) do
	   printf "${val2}"
	  done
	  echo ${val}
 done
}

if [ $1 -eq 1 ]; then
  type1
elif [ $1 -eq 2 ]; then
 type2
elif [ $1 -eq 3 ]; then
 type3
fi
