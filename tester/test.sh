#!/bin/bash

echo ">>>>>>>>VERBOS_TESTER<<<<<<<<<<<<<"

echo "The champions are in ../ressources/vm_champs/champs/"
find .. -name "*.cor"

read -p "Select the champions you whant to test : " champs

if [ -z $champs ]
then

echo "ERROR : Wrong champs path"

else

echo "Store first to exec_1.debug"
../corewar $champs > exec_1.debug

echo "Store second to exec_2.debug"
../ressources/vm_champs/corewar -v 31 $champs > exec_2.debug

echo "Store diff to diff.debug"
read -p "Select arguments for diff : " args
diff $args exec_1.debug exec_2.debug > diff.debug

fi