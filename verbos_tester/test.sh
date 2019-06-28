#!/bin/bash

NOCOLOR='\033[0m'
RED='\033[0;31m'
LIGHTGREEN='\033[1;32m'

PATH_1=../corewar
OPT_1="-v -a"
PATH_2=../ressources/vm_champs/corewar
OPT_2="-v 31 -a"

echo -e "${LIGHTGREEN}***********************************************************"
echo -e ">>>>>>>>>>>>>>>>>>>>VERBOS_TESTER<<<<<<<<<<<<<<<<<<<<<<<<<<"
echo -e "***********************************************************${NOCOLOR}"
echo "Select the champions to test ?"
unset options i
while IFS= read -r -d $'\0' f; do
	options[i++]="$f"
done < <(find .. -name "*.cor" -print0 )
let "i = 1"
select champs in "${options[@]}" "stop selection"; do
case $champs in
	*.cor)
		echo "$champs selected"
		if [ $i = 1 ]
		then
			champ1="$champs"
			((i++))
		elif [ $i = 2 ]
		then
			champ2="$champs"
			((i++))
		elif [ $i = 3 ]
		then
			champ3="$champs"
			((i++))
		elif [ $i = 4 ]
		then
			champ4="$champs"
			((i++))
		else
			echo -e "${RED}You already selected 4 champions(MAX)${NOCOLOR}"
			break
		fi
	;;
	"stop selection")
		echo -e "${LIGHTGREEN}Process selection...${NOCOLOR}"
		break
	;;
	*)
		echo "not listed"
	;;
	esac
done

if [ $i = 1 ] && [ -z $champ1]
then
	echo -e "${RED}No champions selected${NOCOLOR}"
	exit
fi

echo -e "${LIGHTGREEN}Store first to exec_1.debug...${NOCOLOR}"
$PATH_1 $OPT_1 $champ1 $champ2 $champ3 $champ4 > exec_1.debug

echo -e "${LIGHTGREEN}Store second to exec_2.debug...${NOCOLOR}"
$PATH_2 $OPT_2 $champ1 $champ2 $champ3 $champ4 > exec_2.debug

read -p "Write here the arguments for diff : " args
read -p "Store the output ? | less ? (y/n/less) " answer2

if [ "$answer2" = "y" ] || [ "$answer2" = "Y" ] || [ "$answer2" = "yes" ]
then
	echo -e "${LIGHTGREEN}Store diff to diff.debug${NOCOLOR}"
	diff $args exec_1.debug exec_2.debug > diff.debug
elif [ "$answer2" = "less" ]
then
	diff $args exec_1.debug exec_2.debug | less
else
	diff $args exec_1.debug exec_2.debug 
fi

if [ $? != 0 ]
then
	echo -e "${RED}[diff error]${NOCOLOR}"
else
	echo -e "${LIGHTGREEN}[diff ok]${NOCOLOR}"
fi
