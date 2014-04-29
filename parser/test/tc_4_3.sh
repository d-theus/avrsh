#!/bin/bash

while read line; do
	echo "-------------"
	./avrsh "$line";
	echo "Status: $?"
	echo "-------------"
done < ./test/tc_4_3_input.txt
