#include <iostream>
#include <SFML/Graphics.hpp>
#include "common.h"
#include "map.h"
#include "matrix.h"
#include "position.h"

int main() {

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;

    const int PIXEL_SIZE = 10; // 10x10 actual pixels for one game pixel

    const int GAME_WIDTH = WINDOW_WIDTH / PIXEL_SIZE;
    const int GAME_HEIGHT = WINDOW_HEIGHT / PIXEL_SIZE;

    std::cout << "***** SNAKE v1 *****\n";
    std::cout << "Press enter when you are ready to play !";
    
    Map map(GAME_HEIGHT, GAME_WIDTH);
    std::cin.get();
   
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Schnek");
    
    sf::Clock clock;
    sf::Time tickDuration = sf::milliseconds(50);

    Position position(0,0);
    sf::RectangleShape newShape(sf::Vector2f(10, 10));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    map.setDirection(Direction::Up);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    map.setDirection(Direction::Down);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    map.setDirection(Direction::Left);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    map.setDirection(Direction::Right);
                }
            
            }

        }
        
        
        if (clock.getElapsedTime() > tickDuration && !map.gameLost) {
            window.clear();
            map.iterateTick();
            clock.restart();


            for(int row = 0; row < GAME_HEIGHT; row++) {
                for(int col = 0; col < GAME_WIDTH; col++) {
                    position.x = row;
                    position.y = col;
                    switch(map.matrix(row, col)) {
                        case MapObject::Empty:
                            newShape.setPosition(col*10, row*10);
                            newShape.setFillColor(sf::Color::Black);
                            window.draw(newShape);
                            break;
                        case MapObject::Snake:
                            newShape.setPosition(col*10, row*10);
                            newShape.setFillColor(sf::Color::Green);
                            window.draw(newShape);
                            break;
                        case MapObject::Apple:
                            newShape.setPosition(col*10, row*10);
                            newShape.setFillColor(sf::Color::Red);
                            window.draw(newShape);
                            break;
                    }
                }
            }
            window.display();
        }
        if (map.gameLost){
            std::cout << "GAME LOST CYKA BLYAT" << std::endl;
            return 0;
        }
    }

    return 0;
}

