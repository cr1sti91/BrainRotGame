#include "auxFunctions.h"

bool circleBorderCollision(sf::CircleShape circle, const sf::RectangleShape& rect, 
                           const sf::Vector2f& velocityUV, const float dt) 
{                                
    circle.move(dt * bulletsSpeed * velocityUV);
            
    const sf::Vector2f circlePos = circle.getPosition(); 
    const sf::FloatRect rectDim = rect.getGlobalBounds(); 
    
    if(circlePos.x - bulletsRadius < rectDim.left || circlePos.x + bulletsRadius > rectDim.left + rectDim.width
        || circlePos.y - bulletsRadius < rectDim.top || circlePos.y + bulletsRadius > rectDim.top + rectDim.height  )
        return true; // Bullet-ul a ajuns la margine   
   return false; 
}  