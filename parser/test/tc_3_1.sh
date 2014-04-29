#!/bin/bash

while read line; do
	echo "-------------"
	./avrsh "$line";
	echo "Status: $?"
	echo "-------------"
done < ./test/tc_3_1_input.txt
