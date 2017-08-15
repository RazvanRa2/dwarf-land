#!/bin/bash

testsNumber=10
executable=dwarfland
total=0
test=0
((punctajTotal = 9 * $testsNumber))

make build >/dev/null

if test ! -x $executable; then
    echo "Executable file missing."
    exit 1
fi

for (( test=1; test<=$testsNumber; test++ )) do
	cp ./bonus/inputs/$test ./dwarfland.in
	./$executable <dwarfland.in >dwarfland.out
	if test ! -x $executable; then
    	echo "Output file missing."
    	exit 1
	fi
	mkdir ./tmp; cd ./tmp
	head -n 2 ../dwarfland.out >first
	tr -s ' ' '\n' <first >firstSplit
	head -n 1 firstSplit > task1
	cat firstSplit | head -n 2 | tail -n 1 > task2
	cat first | head -n 2 | tail -n 1 > bonus
	
	head -n 2 ../bonus/outputs/$test >first.ref
	tr -s ' ' '\n' <first.ref >firstSplit.ref
	head -n 1 firstSplit.ref > task1.ref
	cat firstSplit.ref | head -n 2 | tail -n 1 > task2.ref
	cat first.ref | head -n 2 | tail -n 1 > bonus.ref
	
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

	if diff -q bonus bonus.ref >/dev/null;  then
		echo "Bonus .......................... passed."
		((total = $total + 1))
	else
		echo "Bonus .......................... failed."
	fi
	cd ..
	rm -r tmp
	rm dwarfland.in
	rm dwarfland.out
done
make clean >/dev/null
echo "TOTAL $total / $punctajTotal"



