#include "game.h"

void Game::initShapes()
{
    this->borderShape = new sf::RectangleShape(borderSize);
    this->borderShape->setFillColor(sf::Color(28, 18, 18));  
    this->borderShape->setOrigin(borderSize.x / 2, borderSize.y / 2); 
    this->borderShape->setPosition(width / 2, height / 2); 
    this->borderShape->setOutlineColor(sf::Color(119, 43, 43)); 
    this->borderShape->setOutlineThickness(10.f);     
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

void Game::updateText()
{
    // Update mouse pos: 
    const sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window); 
    this->xcord.setString("x: " + std::to_string(mousePos.x)); 
    this->ycord.setString("y: " + std::to_string(mousePos.y)); 
}

void Game::updateBullets()
{
//     if(!outOfBounds(this->bullet->getShape(), *this->borderShape))
//         this->bullet->move(std::nullopt); 
    

}

Game::Game(const short width, const short height, const std::string name, unsigned short fLimit)
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
        this->update(); 
        this->render(); 
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
            {
                this->window->close();
            }
        }
	}

    this->updateText(); 
    this->updateBullets(); 
}

void Game::render()
{
    this->window->clear(sf::Color(55, 55, 55)); 

	// Rendering game
    this->window->draw(*this->borderShape); 

    this->window->draw(this->xcord); 
    this->window->draw(this->ycord); 

    this->window->draw(this->bullet->getShape()); 

	this->window->display(); 
}
