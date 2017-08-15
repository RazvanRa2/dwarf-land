#!/bin/bash

testsNumber=10
executable=dwarfland
total=0
test=0
((punctajTotal = 8 * $testsNumber))

make build >/dev/null

if test ! -x $executable; then
    echo "Executable file missing."
    exit 1
fi

for (( test=1; test<=$testsNumber; test++ )) do
	cp ./inputs/$test ./dwarfland.in
	./$executable <dwarfland.in >dwarfland.out
	if test ! -x $executable; then
    	echo "Output file missing."
    	exit 1
	fi
	mkdir ./tmp; cd ./tmp
	head -n 1 ../dwarfland.out >first
	tr -s ' ' '\n' <first >firstSplit
	head -n 1 firstSplit > task1
	cat firstSplit | head -n 2 | tail -n 1 > task2
	
	head -n 1 ../outputs/$test >first.ref
	tr -s ' ' '\n' <first.ref >firstSplit.ref
	head -n 1 firstSplit.ref > task1.ref
	cat firstSplit.ref | head -n 2 | tail -n 1 > task2.ref
	
	echo "Test $test"
	if diff -q task1 task1.ref >/dev/null;  then
		echo "Task1 .......................... passed."
		((total = $total + 5))
	else 
		echo "Task1 .......................... failed."
	fi
	
	if diff -q task2 task2.ref >/dev/null;  then
		echo "Task2 .......................... passed."
		((total = $total + 3))
	else
		echo "Task2 .......................... failed."
	fi
	cd ..
	rm -r tmp
	rm dwarfland.in
	rm dwarfland.out
done
make clean >/dev/null
echo "TOTAL $total / $punctajTotal"



