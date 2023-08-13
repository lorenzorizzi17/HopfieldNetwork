
#include"Matrix.hpp"
#include"HopNetwork.hpp"
#include<vector>
#include<algorithm>
#include<SFML/Graphics.hpp>


int main() {
    //setting random seed
    srand((unsigned) time(NULL));

    //graphic constants and parameters
    const int N =15*15;     //n. of HopNetwork (perfect square)
    const int n = std::sqrt(N);
    unsigned const display_height = 0.9 * sf::VideoMode::getDesktopMode().height; //=768
    int const fps = 60;
    int const R = display_height/(4*n);
    double alpha = (double) 1/N;     //hebbian factor
    double evoPerClick = N/10;   



    //random creation of the initial network state
    HopNetwork network = HopNetwork(N);
    
     
    //defining the memories vector (initially empty)
    std::vector<HopNetwork> memories;

    //defining the synaptic matric (initially all 0s)
    Matrix J = Matrix(N,0);
    
    //some graphic stuff (windows, buttons, HopNetwork...)
    sf::Color color(157,154,183);
    sf::Color gray(182,173,173);

    sf::RenderWindow window(sf::VideoMode(display_height, display_height), "Hopfield Network", sf::Style::Default);
    window.setFramerateLimit(fps);

    sf::RectangleShape buttonMemory(sf::Vector2f(250.f, 55.f)); 
    buttonMemory.setPosition(0.38*display_height,0.1*display_height);
    buttonMemory.setFillColor(color);
    sf::RectangleShape buttonRemove(sf::Vector2f(200.f,30.f));
    buttonRemove.setPosition(0.38*display_height,0.9*display_height);
    buttonRemove.setFillColor(color);
    sf::RectangleShape buttonShuffle(sf::Vector2f(200.f, 30.f));
    buttonShuffle.setPosition(0.38*display_height,0.85*display_height);
    buttonShuffle.setFillColor(color);

    sf::Font font;
    if (!font.loadFromFile("graphics/font.ttf")){
        std::cerr << "Errore nel caricamento del font";
    }
    sf::Text textSaveMemory;
    sf::Text textShuffle;
    sf::Text textRemoveMemory;
    textSaveMemory.setFont(font);
    textSaveMemory.setString("Save memory");
    textSaveMemory.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textSaveMemory.setPosition(0.4*display_height,0.1*display_height);
    textSaveMemory.setFillColor(sf::Color::Black);
    textShuffle.setFont(font);
    textShuffle.setCharacterSize(20);
    textShuffle.setString("Shuffle HopNetwork");
    textShuffle.setStyle(sf::Text::Bold);
    textShuffle.setPosition(0.4*display_height,0.85*display_height);
    textShuffle.setFillColor(sf::Color::Black);
    textRemoveMemory.setFont(font);
    textRemoveMemory.setCharacterSize(20);
    textRemoveMemory.setString("Remove memories");
    textRemoveMemory.setStyle(sf::Text::Bold);
    textRemoveMemory.setPosition(0.4*display_height,0.9*display_height);
    textRemoveMemory.setFillColor(sf::Color::Black);

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
                if(event.key.code==sf::Keyboard::Space){
                    for(int i =0; i < evoPerClick; i++){
                        network.evolveRandom2(J);
                    }
                    //compute and print energy
                    std::cout << "\nEnergy of the system is: " << network.printEnergy(J) << '\n';
                } else if (event.key.code==sf::Keyboard::L){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        network.drawL(false);
                    } else {
                        network.drawL(true);
                    }
                } else if (event.key.code==sf::Keyboard::X){
                    network.drawX();
                } else if (event.key.code==sf::Keyboard::T){
                    network.drawT();
                } else if (event.key.code==sf::Keyboard::O){
                    network.drawO();
                } else if (event.key.code==sf::Keyboard::Z){
                    network.drawZ();
                } 
                else if (event.key.code==sf::Keyboard::P){
                    std::cerr << "\nDistances are: (" << network.distance2From(memories) << '\n';
                } else if (event.key.code==sf::Keyboard::N){
                    network.evolveUntilConverge(1000,J);
                } 
                else if (event.key.code ==sf::Keyboard::Num0){
                    network.setState(memories[0].getVector());
                }
                else if (event.key.code ==sf::Keyboard::Num1){
                    network.setState(memories[1].getVector());
                }
                else if (event.key.code ==sf::Keyboard::Num2){
                    network.setState(memories[2].getVector());
                }
                else if (event.key.code ==sf::Keyboard::Num3){
                    network.setState(memories[3].getVector());
                }
                else if (event.key.code == sf::Keyboard::C){
                    double corr = 0;
                    for (int i = 0; i < N; i++)
                    {
                        corr+= ((memories[0].getVector())[i])*((memories[1].getVector())[i]);
                    }
                    std::cerr << "Correlation is: " << corr << '\n';
                }
            }
            
            if (event.type ==sf::Event::MouseButtonPressed){
                //change the states by pressing on HopNetwork
                if (event.mouseButton.button == sf::Mouse::Right){
                    double x = event.mouseButton.x;
                    double y = event.mouseButton.y;
                    double max = std::max(std::abs(0.5*display_height-x),std::abs(0.5*display_height-y));
                    if ((max < 0.25*display_height)){
                        int i = (x-(display_height/4))/(display_height/(2*n));
                        int j = (y-(display_height/4))/(display_height/(2*n));
                        network.setState(n*j+i,network.getState(n*j+i)*(-1));
                    }
                }
                
                //saving memory
                if (event.mouseButton.button == sf::Mouse::Left){
                    double x = event.mouseButton.x;
                    double y = event.mouseButton.y;
                    //pressed save memory
                    if (((x-0.38*display_height> 0)&&(x-0.38*display_height<250.f))&&(((y-0.1*display_height> 0)&&(y-0.1*display_height<30.f))))
                    {
                        network.saveAsMemory(memories, J, alpha);
                        std::cerr << "\nSaved memory!\n";
                        std::cerr << "\nYou have now succesfully stored " << memories.size() << " memories\n";
                    }
                    //removing memories
                    if (((x-0.38*display_height> 0)&&(x-0.38*display_height<200.f))&&(((y-0.9*display_height> 0)&&(y-0.9*display_height<30.f))))
                    {
                        network.removeMemories(memories,J);
                        std::cerr << "\nRemoving all memories\n";
                    }
                    
                    //pressed shuffle HopNetwork
                    if (((x-0.38*display_height> 0)&&(x-0.38*display_height<200.f))&&(((y-0.85*display_height> 0)&&(y-0.85*display_height<45.f))))
                    {
                        std::cerr << "\nShuffling HopNetwork\n";
                        HopNetwork n = HopNetwork(N);
                        network.setState(n.getVector());
                    }
                }
            }
        }

        //drawing the necessary
        window.clear(sf::Color::White);
        //drawing the HopNetwork with their activation value
        for (int i = 0; i < N; i++)
        {
            sf::CircleShape unity(R);
            double L = display_height/(2*n);
            int column = i%n;
            int row = (i-column)/n;
            unity.setOrigin(R/2,R/2);
            unity.setPosition(0.25*display_height + (0.5+column)*L , 0.25*display_height + L*(row+0.5));
            if (network.getState(i)==1) {
                unity.setFillColor(sf::Color::Black);
            } else if (network.getState(i)==-1){
                unity.setFillColor(gray);
            }
            window.draw(unity);
        }
        //drawing text, button
        window.draw(buttonMemory);
        window.draw(buttonShuffle);
        window.draw(textSaveMemory);
        window.draw(textShuffle);
        window.draw(buttonRemove);
        window.draw(textRemoveMemory);
        
        window.display();
    }

}