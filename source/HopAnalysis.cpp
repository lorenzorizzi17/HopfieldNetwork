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
    const int N =100;
    double alpha = (double) 1/N;     //hebbian factor 

    //random creation of the initial network state
    HopNetwork network = HopNetwork(N);

    //creating the synaptic matrix
    Matrix J = Matrix(N,0);
    
    //defining the memories vector (initially empty)
    std::vector<HopNetwork> memories;

    std::ofstream fileTest1;
    std::ofstream fileTest2;
    std::ofstream fileTest3;
    
    int test=1;
    /* std::cout << "\nInsert test code: ";
    std::cin >> test; */
    //Running simulation number 1: given n random memories, we will test whether random initial state of the netwok
    //will converge to real memories or to fictitious memories we didn't explicitly stored
    if (test==1)
    {
        std::cout << "\nStoring p random memories and studying the convergence of random initial state...\n";
        
        int p = 4; //number of memories to be stored
        int N_cycles = 100;  //number of cycles to perform 

        std::string name = "/home/lorenzo17/HopfieldNetwork/data/test1_" +  to_string(N) +"_"+to_string(p)+ ".txt";
        fileTest1.open(name);
        
        //creating n random memories
        for (int i = 0; i < p; i++)
        {
            HopNetwork memory = HopNetwork(N);
            memory.saveAsMemory(memories, J, alpha);
        }

        for (int i = 0; i < N_cycles; i++)
        {
            network = HopNetwork(N); //random setting the initial state
            network.evolveUntilConverge(1000,J); 
            
            //computing the distance of the converged state from the memories and printing it onto the file .txt
            std::vector<double> distanceFromMemories;
            for (int k = 0; k < p;k++)
            {
                int d = network.distance2From(memories[k]);
                distanceFromMemories.push_back(d);
                if ((d == 0)||(d==std::sqrt(N)*2))
                {
                    fileTest1 << k+1 << std::endl;
                }
            }
            auto it0 = std::find(distanceFromMemories.begin(), distanceFromMemories.end(),0);
            auto it30 = std::find(distanceFromMemories.begin(), distanceFromMemories.end(),std::sqrt(N)*2);
            if ((it0==distanceFromMemories.end())&&(it30==distanceFromMemories.end()))
            {
                fileTest1 << p+1 << std::endl;
            }
            distanceFromMemories.clear();
            //std::cerr << (double)i/N_cycles*100 << " \% \n";
        }
        fileTest1.close();


    } else if (test==2){

        /* HopNetwork network = HopNetwork(N);
        std::vector<std::vector<double>> memories;

        std::cout << "\nStudying the stability of p random stored memories...\n";
        fileTest2.open("/home/lorenzo17/HopfieldNetwork/data/test2.txt");
        int p = 10; //number of memories to be stored
        int N_cycles = 100;  //number of cycles to perform 

        //creating n random memories
        for (int i = 0; i < p; i++)
        {
            HopNetwork memory = HopNetwork(N);
            memory.saveAsMemory(memories,alpha);
        }


        for (int i = 0; i < N_cycles; i++)
        {
            //setting the initial state equal to one of the memories
            int n = rand()%p;
            HopNetwork network = memories[n];
            network.evolveUntilConverge(600);
            std::cerr << network.distanceFrom(memories[n]);  //this should be 0 or 30 if the stabilty is assured
        } */


    } else if (test ==3){
        /* std::cout << "\nStudying the stability of p random stored memories adding a little random noise...\n";
        fileTest3.open("/home/lorenzo17/HopfieldNetwork/data/test3.txt");
        int p = 10; //number of memories to be stored
        int N_cycles = 100;  //number of cycles to perform 
        int nRandomNoise = 1; //number of bit to modify from saved memory

        //creating n random memories
        for (int i = 0; i < p; i++)
        {
            HopNetwork memory = HopNetwork(N);
            memory.saveAsMemory(memories,alpha);
        }

        for (int i = 0; i < N_cycles; i++)
        {
            int n = rand()%p;
            HopNetwork network = memories[n];   //starting from a known memory that has been saved
            network.randomNoise(nRandomNoise);  //adding some noise to the memory 
            network.evolveUntilConverge(600);
            std::cerr << network.distanceFrom(memories[n]);
        } */
    }
}