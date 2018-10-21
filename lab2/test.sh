#!/bin/bash

for i in 0 1 2 3 4
do
	g++ file"$i".cpp -o file"$i"
done
