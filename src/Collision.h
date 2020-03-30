#pragma once

#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

namespace Collision {
	
	bool PixelPerfectTest( const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit, std::vector<sf::Uint8>& mask );
	
}

#endif	/* COLLISION_H */