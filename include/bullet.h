#include "additional.h"

class Bullet
{
private: 
    sf::Texture* texture; 
    sf::Sprite* sprite; 
    float movementSpeed; 
    float radius; 
    float angle; 

public: 
    Bullet(); 
    ~Bullet(); 

    void move(const std::optional<float> newAngle); 

    const sf::Sprite& getShape() const; 
    const float getAngle() const; 
}; 