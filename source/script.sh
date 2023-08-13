#!/bin/bash
for i in 1 2 3 4 5
do
sudo ./HopAnalysis.out
root -b -l <<EOF
.X HopfieldROOT.cpp
EOF
done