#include "bullet.h"

Bullet::Bullet()
{
    this->shape = new sf::CircleShape(bulletsRadius); 
    this->shape->setRadius(bulletsRadius); 
    this->shape->setFillColor(sf::Color::White); 
    this->shape->setOrigin(bulletsRadius, bulletsRadius); 
    this->shape->setPosition(bulletsInitPos); 

    this->movementSpeed = bulletsSpeed; 
    this->velocityUV = bulletsVelocityDir; // Directia initiala este direct in sus
}

Bullet::~Bullet() { delete this->shape; }   

void Bullet::move(const std::optional<sf::Vector2f> newVelocityUV, const float dt)
{
    if(newVelocityUV.has_value())    
    {
        this->velocityUV = newVelocityUV.value(); 
        if (this->velocityUV.x > 1) this->velocityUV.x = 1; 
        if (this->velocityUV.x < -1) this->velocityUV.x = -1; 
        if (this->velocityUV.y > 1) this->velocityUV.y = 1; 
        if (this->velocityUV.y < -1) this->velocityUV.y = -1; 
    }

    this->shape->move(dt * bulletsSpeed * velocityUV);
}

const sf::CircleShape& Bullet::getShape() const { return *this->shape; }
const sf::Vector2f& Bullet::getVelocityUV() const { return this->velocityUV; }

sf::Clock& Bullet::getClock() { return this->clock; }
