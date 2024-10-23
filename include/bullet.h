#include "auxFunctions.h"

class Bullet
{
private: 
    sf::Clock clock; 
    sf::CircleShape* shape; 
    sf::Vector2f velocityUV; // unit vectors
    float movementSpeed; 
    float radius; 
     
public: 
    Bullet(); 
    ~Bullet(); 

    void move(const std::optional<sf::Vector2f> newVelocityUV, const float dt); 

    const sf::CircleShape& getShape() const; 
    const sf::Vector2f& getVelocityUV() const; 
    sf::Clock& getClock(); 
}; 