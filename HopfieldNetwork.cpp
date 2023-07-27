#include "Matrix.hpp"
#include "Neurons.hpp"
#include<vector>
#include<algorithm>
#include <SFML/Graphics.hpp>


int main() {
    srand((unsigned) time(NULL));
    unsigned const display_height = 0.95 * sf::VideoMode::getDesktopMode().height; //=768
    int const R = 100;
    int const fps = 60;
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

    
    //graphics
    sf::RenderWindow window(sf::VideoMode(display_height, display_height), "Hopfield Network", sf::Style::Default);
    window.setFramerateLimit(fps);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type==sf::Event::KeyPressed)
                {
                    initialState.evolve(J);
                }
        }
        window.clear(sf::Color::White);
        //draw the neurons
        for (int i = 0; i < N; i++)
        {
            double theta = 2*M_PI/N * i;
            sf::CircleShape unity(10);
            unity.setPosition(0.5*display_height+R*std::sin(theta),0.5*display_height-R*std::cos(theta));
            if (initialState.getState(i)==1) {
                unity.setFillColor(sf::Color::Blue);
            } else {
                unity.setFillColor(sf::Color::Red);
            }
            window.draw(unity);
        }
        

        //neurons evolution
        

        window.display();
    }
    

    std::cout << "\nPrinting final state...\n";
    initialState.printStatus();
    std::cout << "\nThe quadratic distance between the final state and the memory is " << initialState.distance2From(memory) << '\n';
    
}