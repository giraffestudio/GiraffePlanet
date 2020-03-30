#include <SFML/Graphics.hpp>
#include <map>
#include "Collision.h"

namespace Collision
{
	sf::Uint8 GetPixel( const std::vector<sf::Uint8>& mask, const sf::Texture* tex, unsigned int x, unsigned int y )
	{
			if ( x > tex->getSize().x || y > tex->getSize().y )
				return 0;

			return mask[static_cast<size_t>(x) + static_cast<size_t>(y) * tex->getSize().x];
	};

	bool PixelPerfectTest( const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit, std::vector<sf::Uint8>& mask )
	{
		sf::FloatRect Intersection;
		if ( Object1.getGlobalBounds().intersects( Object2.getGlobalBounds(), Intersection ) ) {
			sf::IntRect O1SubRect = Object1.getTextureRect();
			sf::IntRect O2SubRect = Object2.getTextureRect();

			std::vector<sf::Uint8> mask1 = mask;
			std::vector<sf::Uint8> mask2 = mask;
			int j = 22;
			// Loop through our pixels
			for ( int i = static_cast<int>(Intersection.left); i < Intersection.left + Intersection.width; i++ ) {
				for ( int j = static_cast<int>(Intersection.top); j < Intersection.top + Intersection.height; j++ ) {

					sf::Vector2f o1v = Object1.getInverseTransform().transformPoint( static_cast<float>(i), static_cast<float>(j) );
					sf::Vector2f o2v = Object2.getInverseTransform().transformPoint( static_cast<float>(i), static_cast<float>(j) );

					// Make sure pixels fall within the sprite's subrect
					if ( o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
						o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
						o2v.x < O2SubRect.width && o2v.y < O2SubRect.height ) {

						if ( GetPixel( mask1, Object1.getTexture(), (int)( o1v.x ) + O1SubRect.left, (int)( o1v.y ) + O1SubRect.top ) > AlphaLimit &&
							GetPixel( mask2, Object2.getTexture(), (int)( o2v.x ) + O2SubRect.left, (int)( o2v.y ) + O2SubRect.top ) > AlphaLimit )
							return true;
					}
				}
			}
		}
		return false;
	}
}