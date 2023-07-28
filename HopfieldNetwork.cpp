
#include"Matrix.hpp"
#include"Neurons.hpp"
#include<vector>
#include<algorithm>
#include<SFML/Graphics.hpp>


int main() {
    srand((unsigned) time(NULL));

    //graphic constants and parameters
    const int N = 25;     //n. of neurons (perfect square)
    const int n = std::sqrt(N);
    unsigned const display_height = 0.95 * sf::VideoMode::getDesktopMode().height; //=768
    int const fps = 60;
    int const R = display_height/(4*n);


    //random creation of the initial network state
    Neurons initialState = Neurons(N);
    
     
    //defining the memories vector (initially empty)
    std::vector<Neurons> memories;


    //defining the synaptic matric (initially all 0s)
    Matrix J = Matrix(N,0.f);
    
    
    //some graphic stuff (windows, buttons, neurons...)
    sf::RenderWindow window(sf::VideoMode(display_height, display_height), "Hopfield Network", sf::Style::Default);
    window.setFramerateLimit(fps);

    sf::RectangleShape buttonMemory(sf::Vector2f(250.f, 55.f)); 
    buttonMemory.setPosition(0.38*display_height,0.1*display_height);
    sf::Color color(157,154,183);
    buttonMemory.setFillColor(color);

    sf::Font font;
    if (!font.loadFromFile("font.ttf")){
        std::cerr << "Errore nel caricamento del font";
    }
    sf::Text text;
    text.setFont(font);
    text.setString("Save memory");
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(0.4*display_height,0.1*display_height);
    text.setFillColor(sf::Color::Black);
    
    //graphic loop
    while (window.isOpen())
    {
        //handling the events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            //evolve
            if (event.type==sf::Event::KeyPressed){
                initialState.evolveRandom(J);
            }
            if (event.type ==sf::Event::MouseButtonPressed){
                //change the states by pressing on neurons
                if (event.mouseButton.button == sf::Mouse::Right){
                    double x = event.mouseButton.x;
                    double y = event.mouseButton.y;
                    double max = std::max(std::abs(0.5*display_height-x),std::abs(0.5*display_height-y));
                    if ((max < 0.25*display_height)){
                        int i = (x-(display_height/4))/(display_height/(2*n));
                        int j = (y-(display_height/4))/(display_height/(2*n));
                        initialState.setState(n*j+i,initialState.getState(n*j+i)*(-1));
                    }
                }
                //saving memory
                if (event.mouseButton.button == sf::Mouse::Left){
                    double x = event.mouseButton.x;
                    double y = event.mouseButton.y;
                    if (((x-0.38*display_height> 0)&&(x-0.38*display_height<250.f))&&(((y-0.1*display_height> 0)&&(y-0.1*display_height<55.f))))
                    {
                        std::cerr << "\nSaved memory!\n";
                        memories.push_back(initialState);
                         for (int i = 0; i < N; i++)
                        {
                            for (int j = 0; j< N; j++)
                            {
                                double invN = 1/(double)N;
                                double coefficient = J.get(i,j)+initialState.getState(i)*initialState.getState(j)/invN;
                                J.set(i,j, coefficient);
                            } 
                        }
                    }
                }
            }
        }

        //drawing the necessary
        window.clear(sf::Color::White);
        //drawing the neurons with their activation value
        for (int i = 0; i < N; i++)
        {
            sf::CircleShape unity(R);
            double L = display_height/(2*n);
            int column = i%n;
            int row = (i-column)/n;
            unity.setOrigin(R/2,R/2);
            unity.setPosition(0.25*display_height + (0.5+column)*L , 0.25*display_height + L*(row+0.5));
            if (initialState.getState(i)==1) {
                unity.setFillColor(sf::Color::Blue);
            } else {
                unity.setFillColor(sf::Color::Red);
            }
            window.draw(unity);
        }
        //drawing text, button
        window.draw(buttonMemory);
        window.draw(text);
        window.display();
    }

}