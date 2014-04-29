#!/bin/bash

while read line; do
	echo "-------------"
	./test/tc_4_4_bin "$line";
	echo "Status: $?"
	echo "-------------"
done < ./test/tc_4_4_input.txt
