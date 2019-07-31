#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable
{
private:	
	sf::IntRect ssRect_green = { 425, 552, 93, 84 };
	sf::Sprite Sprite;
	float Width = 93;
	float Height = 84;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Enemy(float x_pos, float y_pos, sf::Texture &spriteSheet);

	void update(float dt);

	float x;
	float y;
	float rotation = 0;
	float HP = 2;
	
	sf::Rect<float> boundingBox = { 0,0,Width,Height };
};