#include "auxFunctions.h"

// Helper function to check if a pixel is transparent
const bool isPixelTransparent(const sf::Uint8* pixelArray, unsigned int x, unsigned int y, unsigned int width) 
{
	unsigned int index = 4 * (y * width + x);
	return pixelArray[index + 3] == 0; // Check alpha value (4th element in the pixel)
									   // Daca a patra valoare ce descrie pixelul este nula, atunci acesta este transparent
}


const bool outOfBounds(const sf::Shape& shape_1, const sf::Shape& shape_2) 
{
	// Get the bounding boxes of the sprites
	sf::FloatRect bounds1 = shape_1.getGlobalBounds();
	sf::FloatRect bounds2 = shape_2.getGlobalBounds();

	// Check if the bounding boxes intersect
	if (!bounds1.intersects(bounds2)) 
	{
		return false;
	}

	// Get the intersection rectangle
	sf::FloatRect intersection;
	bounds1.intersects(bounds2, intersection);

	// Get textures and pixel data of the sprites
	const sf::Texture* texture1 = shape_1.getTexture();
	const sf::Texture* texture2 = shape_2.getTexture();

	sf::Image image1 = texture1->copyToImage();
	sf::Image image2 = texture2->copyToImage();

	// Get the local bounding boxes (relative to the sprites' positions)
	sf::IntRect localBounds1 = shape_1.getTextureRect();
	sf::IntRect localBounds2 = shape_2.getTextureRect();

	// Loop through the intersection rectangle and check pixels
	for (int i = intersection.left; i < intersection.left + intersection.width; ++i) 
	{
		for (int j = intersection.top; j < intersection.top + intersection.height; ++j) 
		{
			// Calculate the positions in local texture space
			sf::Vector2f localPos1 = shape_1.getInverseTransform().transformPoint(i, j);
			sf::Vector2f localPos2 = shape_2.getInverseTransform().transformPoint(i, j);

			// Check bounds
			if (localPos1.x < 0 || localPos1.x >= localBounds1.width || localPos1.y < 0 || localPos1.y >= localBounds1.height ||
				localPos2.x < 0 || localPos2.x >= localBounds2.width || localPos2.y < 0 || localPos2.y >= localBounds2.height) 
			{
				return true;
			}

			// Check transparency
			if (!isPixelTransparent(image1.getPixelsPtr(), localPos1.x, localPos1.y, localBounds1.width) &&
				!isPixelTransparent(image2.getPixelsPtr(), localPos2.x, localPos2.y, localBounds2.width)) 
			{
				return false; // Collision detected
			}
		}
	}

	return true;
}