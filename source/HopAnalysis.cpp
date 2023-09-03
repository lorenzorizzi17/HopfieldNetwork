#include"Matrix.hpp"
#include"HopNetwork.hpp"
#include<vector>
#include<algorithm>
#include<iostream>
#include <fstream>

////////////////////////////////////////////////////////////////////////////////////////
// This code file is used to test some properties of the Hop Network. Once compiled,  //
// the user can pass an integer value to the main function depending on the test he   //
// wants to execute (possible values: 1-2-3-4)                                        //
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv){
    //setting random seed
    srand((unsigned) time(NULL));

    //Parameters of the simulation
    const int N = 100;
    double alpha = (double) 1/N;     //hebbian factor 

    //random creation of the initial network state
    HopNetwork network = HopNetwork(N);

    //handling the io files
    std::ofstream fileTest1;
    std::ofstream fileTest2;
    std::ofstream fileTest3;
    std::ofstream fileTest4;
    
    std::string test = argv[1];
    int a = stoi(argv[argc-1]);

    
    if (test=="1")
    {
        //Running simulation number 1: given n random memories, we will test whether random initial state of the netwok
        //will converge to real memories or to fictitious memories we didn't explicitly stored

        int p = a; //number of memories to be stored
        int N_cycles = 1000;  //number of cycles to perform 
        std::cout << "\nStoring p random memories and studying the convergence of random initial state...\n";
        
        std::string name = "/home/lorenzo17/HopfieldNetwork/data/test1_" +  to_string(N) +"_"+to_string(p)+ ".txt";
        fileTest1.open(name);
        
        //creating p random memories
        for (int i = 0; i < p; i++)
        {
            network.randomShuffle(N);
            network.saveAsMemory(alpha);
        }

        int counter = 0;
        for (int i = 0; i < N_cycles; i++)
        {
            network.randomShuffle(N);     //random setting the initial state
            network.evolveUntilConverge(1000); //let the system evolve until strong convergence
            //computing the distance of the converged state from the memories and printing it onto the file .txt
            std::vector<double> distanceFromMemories;
            for (int k = 0; k < p; k++)
            {
                int d = network.distanceFrom(network.getMemory(k));
                distanceFromMemories.push_back(d);
                if ((d == 0)||(d==(int)(N)*2))
                {
                    fileTest1 << k+1 << std::endl;
                }
            }
            auto it0 = std::find(distanceFromMemories.begin(), distanceFromMemories.end(),0);
            auto it30 = std::find(distanceFromMemories.begin(), distanceFromMemories.end(),(int)N*2);
            if ((it0==distanceFromMemories.end())&&(it30==distanceFromMemories.end()))
            {
                fileTest1 << p+1 << std::endl;
                counter++;
            }
            distanceFromMemories.clear();
            //std::cerr << (double)i/N_cycles*100 << " \% \n";
            
        }
        std::cerr << "When p =" << p << " , then number of fictitious memory is " << counter << '\n';
        fileTest1.close();


    } else if (test=="2"){

        //Running simulation n.2: we will be testing the stability of the p stored memories

        std::cout << "\nStudying the stability of p random stored memories...\n";
        fileTest2.open("/home/lorenzo17/HopfieldNetwork/data/test2.txt");
        int p = 10; //number of memories to be stored
        int N_cycles = 500;  //number of cycles to perform 

        //creating p random memories
        for (int i = 0; i < p; i++)
        {
            network.randomShuffle(N);
            network.saveAsMemory(alpha);
        }


        for (int i = 0; i < N_cycles; i++)
        {
            //setting the initial state equal to one of the memories
            int n = rand()%p;
            network.setState(network.getMemory(n));
            network.evolveUntilConverge(1000);
            std::cerr << network.distanceFrom(network.getMemory(n));  //this should be 0 if the stabilty is assured
        }


    } else if (test =="3"){
        //Running test number 3. We will study the stability of memory to which random noise has been added and its 
        //capability to retrieve the initial memory
        fileTest3.open("/home/lorenzo17/HopfieldNetwork/data/test3.txt", std::ios::app);

        int p = 13; //number of memories to be stored
        int N_cycles = 200;  //number of cycles to perform 
        int nRandomNoise = a*N; //number of bit to modify from saved memory

        std::cout << "\nStudying the stability of p random stored memories adding a little random noise (altering " << nRandomNoise <<" bits)...\n";
        
        //creating p random memories
        for (int i = 0; i < p; i++)
        {
            network.randomShuffle(N);
            network.saveAsMemory(alpha);
        }
        
        int counter = 0;
        for (int i = 0; i < N_cycles; i++)
        {   
            int n = rand()%p;
            network.setState(network.getMemory(n));   //starting from a known memory that has been saved
            network.randomNoise(nRandomNoise);  //adding some noise to the memory 
            network.evolveUntilConverge(1000);  //let the system evolve untile convergence
            int dist = network.distanceFrom(network.getMemory(n));
            if (dist!=0){counter++;}
        }
        std::cerr << "Number of non-zero: " << (double)counter/(double)N_cycles;
        fileTest3 << (double)counter/(double)N_cycles << std::endl;
        fileTest3.close();
    } else if (test == "4"){
        
        fileTest4.open("/home/lorenzo17/HopfieldNetwork/data/test4.txt", std::ios::app);
        int p = 10; //number of memories to be stored
        int N_cycles = 100;  //number of cycles to perform 
        int nRandomNoise = a*N; //number of bit to modify from saved memory

        std::cout << "\nStudying the stability of p random stored memories adding a little random noise (altering " << nRandomNoise <<" bits)...\n";
        
        //creating p random memories with low correlation
        for (int i = 0; i < p; i++)
        {
            network.randomShuffle(N);
            network.saveAsMemory(alpha);
        }

        Matrix J = network.getMatrix();
        int counter = 0;
        for (int i = 0; i < N_cycles; i++)
        {   
            network.setMatrix(J);
            int n = rand()%p;
            network.setState(network.getMemory(n));   //starting from a known memory that has been saved
            network.randomNoise(nRandomNoise);  //adding some noise to the memory 
            network.randomNoiseOnMatrix(20*N,0);
            network.evolveUntilConverge(1000);
            int dist = network.distanceFrom(network.getMemory(n));
            //std::cerr << dist << '\n';
            if (dist!=0){counter++;}
        }
        std::cerr << "Number of non-zero: " << (double)counter/(double)N_cycles;
        fileTest4 << (double)counter/(double)N_cycles << std::endl;
        fileTest4.close();
    }
}