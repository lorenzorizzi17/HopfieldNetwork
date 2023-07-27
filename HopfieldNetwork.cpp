#include "Matrix.hpp"
#include "Neurons.hpp"
#include<vector>
#include<algorithm>


int main() {
    srand((unsigned) time(NULL));
    const int N = 10;

    //random initializing neurons with the default ctor
    Neurons initialState = Neurons(N); 
    std::cout << "\nPrinting initial state...\n";
    initialState.printStatus();
    
     
    //random initializing a memory
    Neurons memory = Neurons(N);
    std::cout << "\nPrinting memory...\n";
    memory.printStatus();

    //defining the synaptic matrix
    Matrix J = Matrix(N,1.1);
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j<= N; j++)
        {
            double invN = 1/(double)N;
            double coefficient = memory.getState(i-1)*memory.getState(j-1)*invN;
            J.set(i,j, coefficient);
        } 
    }
    std::cout << "\nPrinting synaptic matrix... \n";
    J.print();

    //let the system evolve 
    for (int t = 0; t < 10; t++)
    {
       initialState.evolve(J);
    }
    
    std::cout << "\nPrinting final state...\n";
    initialState.printStatus();
    std::cout << "\nThe quadratic distance between the final state and the memory is " << initialState.distance2From(memory) << '\n';
    
}