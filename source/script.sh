#!/bin/bash
for i in 1 2 3 4 5 6 7 8 9 10
do
sudo ./HopAnalysis.out 3 0.01
done
for i in 1 2 3 4 5 6 7 8 9 10
do
sudo ./HopAnalysis.out 3 0.05
done
for i in 1 2 3 4 5 6 7 8 9 10
do
sudo ./HopAnalysis.out 3 0.1
done
for i in 1 2 3 4 5 6 7 8 9 10
do
sudo ./HopAnalysis.out 3 0.5
done
for i in 1 2 3 4 5 6 7 8 9 10
do
sudo ./HopAnalysis.out 3 0.75
done
#root -b -l <<EOF
#.X HopfieldROOT.cpp
#EOF