#to be executed in the working directory (where source and build directories are)

#!/bin/bash


cmake -S ./source -B ./build -DBUILD_TESTING=ON
cmake --build build
sudo build/HopfieldNetwork.out