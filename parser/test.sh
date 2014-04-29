#!/bin/bash

for input in `ls ./test/tc_*_input.txt`; do
	tcase=`echo $input | sed "s/.*_\(.*\)_\(.*\)_.*/\1_\2/"`
	echo "######################################"
	echo "#########" "TEST CASE" "#########"
	echo "#########" $tcase "#########"
	echo "######################################"
	while read line; do
		echo "Command:" "$line"
		./test/tc_"$tcase"_bin "$line";
	echo "--------------------------------------"
	done < $input;
	echo "######################################"
	echo "######################################"
	echo ''
done
