#!/bin/bash

NOCOLOR='\033[0m'
RED='\033[0;31m'
LIGHTGREEN='\033[1;32m'

echo -e "${LIGHTGREEN}***********************************************************"
echo -e ">>>>>>>>>>>>>>>>>>>>VERBOS_TESTER<<<<<<<<<<<<<<<<<<<<<<<<<<"
echo -e "***********************************************************${NOCOLOR}"

read -p "Do you need to search the champions paths ? (y/n) " answer

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

      	find .. $champs > /dev/null

		if [ $? != 0 ] || [ -z $champs ]
		then
		echo -e "${RED}ERROR : Wrong champions path${NOCOLOR}"

		else
		echo "Store first to exec_1.debug"
		../corewar $champs > exec_1.debug

		echo "Store second to exec_2.debug"
		../ressources/vm_champs/corewar -v 31 $champs > exec_2.debug

		read -p "Select arguments for diff : " args
		read -p "Do you need to store the output | less ? (y/n/less) " answer2

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
      #echo "You chose to stop"
      exit
      ;;
    *)
      echo "This is not a number"
      ;;
  esac
done

fi

read -p "Write here the champions paths you whant to test : " champs

find .. $champs > /dev/null

if [ $? != 0 ] || [ -z $champs ]
then
echo -e "${RED}ERROR : Wrong champions path${NOCOLOR}"

else
echo "Store first to exec_1.debug"
../corewar $champs > exec_1.debug

echo "Store second to exec_2.debug"
../ressources/vm_champs/corewar -v 31 $champs > exec_2.debug

read -p "Select arguments for diff : " args
read -p "Do you need to store the output | less ? (y/n/less) " answer2

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
