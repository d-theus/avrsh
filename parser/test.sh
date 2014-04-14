#!/bin/bash

while read line; do
	echo "######################################"
	./avrsh "$line";
	echo "######################################"
done < ./test_strings.txt
