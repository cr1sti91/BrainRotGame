#include <string>
#include <iostream>
#include <cmath>
#include <optional>

#include <SFML/Graphics.hpp>

//----------------------------------------Window properties----------------------------------------
const float width = 1300;
const float height = 700;
const float frameLimit = 60;
const std::string gameName = "Brain Rot";

//--------------------------------------Game border properties-------------------------------------
const sf::Vector2f borderSize(width - 150, height - 100); 

//----------------------------------------Bullets properties---------------------------------------
const float bulletsRadius = 10; 
const float bulletsSpeed  = 3; 
const sf::Vector2f bulletsInitPos(width / 2, height - 60); 

//---------------------------------------------Paths-----------------------------------------------
const std::string fontPath = "img-fonts-music/Fonts/arial.ttf"; 
const std::string plasmaBallPath = "img-fonts-music/Images/Plasma_ball.png"; 


