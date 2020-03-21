#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "ResourceMan.h"
#include "Animation.h"

class Text : public sf::Drawable
{
private:
	sf::Text text;
	sf::Sprite sprite;
	sf::RenderTexture* texture;

	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

public:
	std::vector<Animation> animations;

	enum class Alignement : size_t { XY = 0, HORIZONTAL_CENTER = 1, VERTICAL_CENTER = 2 };


	Text( sf::Font& pfont, unsigned int size, std::string str, size_t position_flags, sf::Vector2f xy = {0.f,0.f} );
	sf::Sprite* getSprite() { return &sprite; };
};

