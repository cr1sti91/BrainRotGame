#pragma once
#include "auxFunctions.h"
#include "bullet.h"


class Game
{
private: 
    sf::RenderWindow* window; 
    sf::Event event; 

    // Shapes
    sf::RectangleShape* borderShape; 
    Bullet* bullet; 

    // Text
    sf::Font font; 
    sf::Text xcord, ycord; 


    // Private methods: init 
    void initShapes(); 
    void initText(); 

    //Private methods: update 
    void updateText(); 
    void updateBullets(); 
    
    
    void update(); 
    void render(); 

public: 
    Game(const short width, const short height, const std::string name, unsigned short fLimit); 
    ~Game(); 

    void run(); 
}; 