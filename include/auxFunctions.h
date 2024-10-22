#include <SFML/Graphics.hpp>

// Helper function to check if a pixel is transparent
const bool isPixelTransparent(const sf::Uint8* pixelArray, unsigned int x, unsigned int y, unsigned int width); 
const bool outOfBounds(const sf::Shape& shape_1, const sf::Shape& shape_2); 