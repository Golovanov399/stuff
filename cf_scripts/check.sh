#!/bin/bash

for i in in*
do
	j=$(echo $i | tail -c +3 | head -c 1)
	out="out$j.out"
	./qwe < $i > "res$j.out"
	if [ -z "$(diff -b res$j.out $out)" ]
	then
		echo "Test $j: ok"
	else
		echo "Test $j: wa"
		echo "Correct answer:"
		cat $out
		echo "Your answer:"
		cat "res$j.out"
	fi
done

