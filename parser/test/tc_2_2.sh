#!/bin/bash

while read line; do
	echo "-------------"
	./avrsh "$line";
	echo "Status: $?"
	echo "-------------"
done < ./test/tc_2_2_input.txt
