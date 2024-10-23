#include <string>
#include <iostream>
#include <cmath>
#include <optional>

#include <SFML/Graphics.hpp>


//----------------------------------------Window properties----------------------------------------
const float width = 1300.f;
const float height = 700.f;
const float frameLimit = 60.f;
const std::string gameName = "Brain Rot";

//--------------------------------------Game border properties-------------------------------------
const sf::Vector2f borderSize(width - 150.f, height - 100.f); 

//------------------------------------Stick shape properties-------------------------------------
const sf::Vector2f stickSize(100.f, 20.f); 
const sf::Vector2f stickInitPos(width / 2, height - 45.f); 
const sf::Vector2f stickVelocityUV(1.f, 0);
const float stickSpeed = 10;  

//----------------------------------------Bullets properties---------------------------------------
const float bulletsRadius = 10.f; 
const float bulletsSpeed  = 400.f; 
const sf::Vector2f bulletsVelocityDir(0.f, -1.f);  
const sf::Vector2f bulletsInitPos(width / 2, height - 90); 


//---------------------------------------------Paths-----------------------------------------------
const std::string fontPath = "img-fonts-music/Fonts/arial.ttf";
