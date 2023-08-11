#include"Matrix.hpp"
#include"HopNetwork.hpp"
#include<vector>
#include<algorithm>
#include<iostream>
#include <iostream>
#include <fstream>



int main(){
    //setting random seed
    srand((unsigned) time(NULL));

    //Parameters of the simulation
    const int N =15*15;
    double alpha = (double) 1/N;     //hebbian factor
    double evoPerClick = N/10;  

    //random creation of the initial network state
    HopNetwork network = HopNetwork(N);
    
    //defining the memories vector (initially empty)
    std::vector<HopNetwork> memories;

    //defining the synaptic matric (initially all 0s)
    Matrix J = Matrix(N,0);

    std::ofstream fileTest1("../ROOT",std::ios::trunc);
    fileTest1.open("test1.txt");




    int test;
    std::cin >> test;
    //Running simulation number 1: given n random memories, we will test whether random initial state of the netwok
    //will converge to real memories or to fictitious memories we didn't explicitly stored
    if (test==1)
    {
        
        int p = 5; //number of memories to be stored
        int N_cycles = 100;  //number of cycles to perform 

        //creating n random memories
        for (int i = 0; i < p; i++)
        {
            HopNetwork memory = HopNetwork(N);
            memory.saveAsMemory(memories,J,alpha);
        }

        for (int i = 0; i < N_cycles; i++)
        {
            HopNetwork network = HopNetwork(N); //random setting the initial state
            double E = 0; //E is the energy associated to the network. Its value (and its stability) will be determine whether
            //the network has already converged to a stable state
            int j = 0;
            while (j<500){
                network.evolveRandom2(J);
                double deltaE = E - network.printEnergy(J);
                if (deltaE < 0.01){
                    j++;
                } else {
                    j=0;
                }
                E = network.printEnergy(J);
            } //at the end of the while cycle, we can assume that the network has reached the convergence pattern 
            
            //computing the distance of the converged state from the memories and printing it onto the file .txt
            std::vector<double> distanceFromMemories;
            for (int k = 0; k< p;k++)
            {
                double d = network.distance2From(memories[k]);
                distanceFromMemories.push_back(d);
                if ((d == 0)||(d==30))
                {
                    fileTest1 << k+1 << std::endl;
                }
            }
            auto it0 = std::find(distanceFromMemories.begin(), distanceFromMemories.end(),0);
            auto it30 = std::find(distanceFromMemories.begin(), distanceFromMemories.end(),30);
            if ((it0==distanceFromMemories.end())&&(it30==distanceFromMemories.end()))
            {
                fileTest1 << p+1 << std::endl;
            }
            
            std::cerr << (double)i/N_cycles*100 << " \% \n";
        }
        fileTest1.close();
    } else if (test==1){
        //test2
    }
    

}