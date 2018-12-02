#!/bin/bash
x=0
for filename in data/*.txt; do
 	mv data/$x.txt query
 	./movie_recommender query/$x.txt data/*
 	mv query/$x.txt data
    x=`expr $x + 1`
done


