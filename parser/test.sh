#!/bin/bash

while read line; do
	echo "######################################"
	echo "$line"
	./avrsh "$line";
	echo "######################################"
done < ./test_strings.txt
