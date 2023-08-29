#to be executed in the working directory (where source and build directories are)

#!/bin/bash
cd source
g++ main2.cpp HopNetwork.cpp state.cpp -o HopNetwork.out -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system
sudo ./HopNetwork.out 
cd ..