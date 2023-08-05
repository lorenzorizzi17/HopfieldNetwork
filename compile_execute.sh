#to be executed in the working directory (where source and build directories are)

#!/bin/bash


cmake -S ./source -B ./build
cd build
make
cd ..
sudo ./build/HopfieldNetwork.out