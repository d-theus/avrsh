#!/bin/bash

while read line; do
	echo "-------------"
	./avrsh "$line";
	echo "Status: $?"
	echo "-------------"
done < ./test/tc_4_5_input.txt
