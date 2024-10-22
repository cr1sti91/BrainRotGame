#include "bullet.h"

Bullet::Bullet()
{
    this->texture = new sf::Texture();

    if(!this->texture->loadFromFile(plasmaBallPath))
        std::cerr << "ERROR::Bullet::Bullet::Plasma_ball.png inaccesibil!" << std::endl;

    this->sprite = new sf::Sprite(*this->texture); 
    this->sprite->setOrigin(this->sprite->getGlobalBounds().width / 2, 
                            this->sprite->getGlobalBounds().height / 2); 
    this->sprite->setPosition(bulletsInitPos);  
    this->sprite->setScale(0.06f, 0.06f); 

    this->movementSpeed = bulletsSpeed; 
    this->angle = 0; 
}

Bullet::~Bullet() 
{ 
    delete this->sprite; 
    delete this->texture; 
}

void Bullet::move(const std::optional<float> newAngle)
{
    if(newAngle.has_value())
        this->angle = newAngle.value(); 

    this->sprite->move(this->movementSpeed * std::cos((angle - 90) * M_PI / 180), 
                      this->movementSpeed * std::sin((angle - 90) * M_PI / 180));
}

const sf::Sprite& Bullet::getShape() const { return *this->sprite; }
const float Bullet::getAngle() const { return this->angle; }