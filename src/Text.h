#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "ResourceMan.h"
#include "Animation.h"

class Text : public sf::Drawable
{
private:
	sf::Text text;
	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

public:
	enum class TextPosition { CENTERED = 1, DEFINED = 2 };
	Text( sf::Font& pfont, std::string str, TextPosition pos, sf::Vector2f xy = {0.f,0.f} );


};

