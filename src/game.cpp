#include "game.h"

/////////////////////////////////////////////// INIT METHODS /////////////////////////////////////////////////
void Game::initShapes()
{
    this->borderShape = new sf::RectangleShape(borderSize);
    this->borderShape->setFillColor(sf::Color::Transparent);  
    this->borderShape->setOrigin(borderSize.x / 2, borderSize.y / 2); 
    this->borderShape->setPosition(width / 2, height / 2); 
    this->borderShape->setOutlineColor(sf::Color(119, 43, 43)); 
    this->borderShape->setOutlineThickness(10.f);  

    this->stickShape = new sf::RectangleShape(stickSize); 
    this->stickShape->setFillColor(sf::Color::Black); 
    this->stickShape->setOrigin(stickSize.x / 2, stickSize.y / 2); 
    this->stickShape->setPosition(stickInitPos);   
    this->stickShape->setOutlineColor(sf::Color::Green); 
    this->stickShape->setOutlineThickness(5.f);  
}

void Game::initText()
{
    if(!this->font.loadFromFile(fontPath))
        std::cerr << "ERROR::Game::initText::Font inaccesibil!" << std::endl;   

    this->xcord.setFont(this->font); 
    this->ycord.setFont(this->font); 

    this->xcord.setPosition(5.f, 5.f); 
    this->ycord.setPosition(5.f, 22.f); 

    this->xcord.setCharacterSize(18); 
    this->ycord.setCharacterSize(18); 
}

/////////////////////////////////////////////// CONSTRUCTOR - DESTRUCTOR /////////////////////////////////////////////////
Game::Game(const short width, const short height, const std::string name, unsigned short fLimit) 
        : stickIsMovingLeft(false), stickIsMovingRight(false)
{
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), 
                                        name, sf::Style::Close | sf::Style::Titlebar); 
    this->window->setFramerateLimit(fLimit);

    // Init methods
    this->initShapes(); 
    this->initText(); 

    this->bullet = new Bullet(); 
}

Game::~Game()
{
    delete this->window; 
    delete this->borderShape; 
}

void Game::run()
{
    while(this->window->isOpen())
    {
        this->render(); 
        this->update(); 
    }
}


/////////////////////////////////////////////// UPDATE METHODS /////////////////////////////////////////////////
void Game::updateText()
{
    this->xcord.setString("x: " + std::to_string((int)this->bullet->getShape().getPosition().x)); 
    this->ycord.setString("y: " + std::to_string((int)this->bullet->getShape().getPosition().y)); 
}

void Game::updateBullets()
{
    const float dt = this->bullet->getClock().restart().asSeconds(); 
    if(circleBorderCollision(this->bullet->getShape(), *this->borderShape, this->bullet->getVelocityUV(), dt))
    {
        const sf::Vector2f pos = this->bullet->getShape().getPosition(); 
        const sf::FloatRect rect = this->borderShape->getGlobalBounds(); 

        if(pos.x < rect.left + this->bullet->getShape().getRadius() * 2
           || pos.x > rect.left + rect.width - this->bullet->getShape().getRadius() * 2)
           this->bullet->move(sf::Vector2f(-this->bullet->getVelocityUV().x, this->bullet->getVelocityUV().y), dt); 

        if(pos.y <= rect.top + this->bullet->getShape().getRadius() * 2  
           || pos.y >= rect.top + rect.height - this->bullet->getShape().getRadius() * 2)                                                                                                  
           this->bullet->move(sf::Vector2f(this->bullet->getVelocityUV().x, -this->bullet->getVelocityUV().y), dt); 
    }
    else if(this->stickShape->getGlobalBounds().intersects(this->bullet->getShape().getGlobalBounds()))
    {
        if(this->stickIsMovingLeft)
            this->bullet->move(this->bullet->getVelocityUV() - stickVelocityUV, dt); 
        else if(this->stickIsMovingRight)
            this->bullet->move(this->bullet->getVelocityUV() + stickVelocityUV, dt); 
        else
            this->bullet->move(sf::Vector2f(this->bullet->getVelocityUV().x, -this->bullet->getVelocityUV().y), dt);
    }
    else 
    {
        this->bullet->move(std::nullopt, dt);   
    }
}

void Game::updateStick()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (this->stickShape->getPosition().x > this->borderShape->getGlobalBounds().left
                                                + this->stickShape->getSize().x / 2 + 10.f) // + outline
        {
            this->stickShape->move(-stickVelocityUV * stickSpeed); 
            this->stickIsMovingLeft = true; 
            this->stickIsMovingRight = false; 
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if (this->stickShape->getPosition().x < this->borderShape->getGlobalBounds().left 
                                                + this->borderShape->getGlobalBounds().width 
                                                - this->stickShape->getSize().x / 2 - 10.f) // - outline
        {
            this->stickShape->move(stickVelocityUV * stickSpeed); 
            this->stickIsMovingLeft = false; 
            this->stickIsMovingRight = true; 
        }
    }
    else
    {
        this->stickIsMovingLeft = false; 
        this->stickIsMovingRight = false; 
    }
}


void Game::update()
{
    while (this->window->pollEvent(this->event))
	{
        if (this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }
        else if (this->event.type == sf::Event::KeyPressed)
        {
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
        }
	}

    this->updateText(); 
    this->updateBullets(); 
    this->updateStick(); 
}

void Game::render()
{
    this->window->clear(sf::Color(55, 55, 55)); 

	// Rendering game
    this->window->draw(*this->borderShape);
    this->window->draw(*this->stickShape);  

    this->window->draw(this->xcord); 
    this->window->draw(this->ycord); 

    this->window->draw(this->bullet->getShape()); 

	this->window->display(); 
}