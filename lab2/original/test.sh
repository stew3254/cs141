#!/bin/bash

for i in 0 1 2 3 4 
do
	wget tars.clarkson.edu/cs141/lab2/file"$i".cpp
	g++ file"$i".cpp -o file"$i"
done
