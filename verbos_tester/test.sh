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
read -p "Test a single champion ? (y/n) " answer
if [ "$answer" = "y" ] || [ "$answer" = "Y" ] || [ "$answer" = "yes" ]
then
	unset options i
	while IFS= read -r -d $'\0' f; do
		options[i++]="$f"
	done < <(find .. -name "*.cor" -print0 )
	select champs in "${options[@]}" "quit"; do
	case $champs in
	*.cor)
		echo "$champs selected"
		echo "Store first to exec_1.debug"
		$PATH_1 $OPT_1 $champs > exec_1.debug
		let "ret1 = $?"
		if [ $ret1 != 0 ]
		then
			echo -e "${RED}ERROR : Path_1 not found${NOCOLOR}"
		else
			echo -e "${LIGHTGREEN}[ok]${NOCOLOR}"
		fi
		echo "Store second to exec_2.debug"
		$PATH_2 $OPT_2 $champs > exec_2.debug
		let "ret2 = $?"
		if [ $ret2 == 127 ]
		then
			echo -e "${RED}ERROR : Path_2 not found${NOCOLOR}"
		else
			echo -e "${LIGHTGREEN}[ok]${NOCOLOR}"
		fi
		if [ $ret1 != 0 ] || [ $ret2 == 127 ]
		then
			echo -e "${RED}ERROR : diff not possible${NOCOLOR}"
			exit
		else
			read -p "Select arguments for diff : " args
			read -p "Store the output ? | less ? (y/n/less) " answer2
		fi
		if [ "$answer2" = "y" ] || [ "$answer2" = "Y" ] || [ "$answer2" = "yes" ]
		then
			echo "Store diff to diff.debug"
			diff $args exec_1.debug exec_2.debug > diff.debug
		elif [ "$answer2" = "less" ]
		then
			diff $args exec_1.debug exec_2.debug | less
		else
			diff $args exec_1.debug exec_2.debug
		fi
	;;
	"quit")
		exit
	;;
	*)
		echo "not listed"
	;;
	esac
done
fi
find .. -name "*.cor"
read -p "Write here the champions paths to test : " champs
find .. $champs > /dev/null
if [ $? != 0 ] || [ -z $champs ]
then
	echo -e "${RED}ERROR : Wrong champions path${NOCOLOR}"
	exit
else
	echo "Store first to exec_1.debug"
	$PATH_1 $OPT_1 $champs > exec_1.debug
	find .. $PATH_1 > /dev/null
	let "ret1 = $?"
	if [ $ret1 != 0 ]
	then
		echo -e "${RED}ERROR : Path_1 not found${NOCOLOR}"
	else
		echo -e "${LIGHTGREEN}[ok]${NOCOLOR}"
	fi
	echo "Store second to exec_2.debug"
	$PATH_2 $OPT_2 $champs > exec_2.debug
	find .. $PATH_2 > /dev/null
	let "ret2 = $?"
	if [ $ret2 != 0 ]
	then
		echo -e "${RED}ERROR : Path_2 not found${NOCOLOR}"
	else
		echo -e "${LIGHTGREEN}[ok]${NOCOLOR}"
	fi
	if [ $ret1 != 0 ] || [ $ret2 == 127 ]
	then
		echo -e "${RED}ERROR : diff not possible${NOCOLOR}"
		exit
	else
		read -p "Select arguments for diff : " args
		read -p "Store the output ? | less ? (y/n/less) " answer2
	fi
fi
if [ "$answer2" = "y" ] || [ "$answer2" = "Y" ] || [ "$answer2" = "yes" ]
then
	echo "Store diff to diff.debug"
	diff $args exec_1.debug exec_2.debug > diff.debug
elif [ "$answer2" = "less" ]
then
	diff $args exec_1.debug exec_2.debug | less
else
	diff $args exec_1.debug exec_2.debug
fi
