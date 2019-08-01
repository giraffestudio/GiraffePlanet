#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Enemy : public sf::Drawable
{
private:	
	float Width = 93.0f;
	float Height = 84.0f;
	
	sf::IntRect ssRect_green = { 425, 552, 93, 84 };		// Watch for member initialization order !
	sf::Sprite Sprite;
	sf::Texture* spriteSheet;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Enemy(float x_pos, float y_pos, sf::Texture* pSpriteSheet);
	void update(float dt);
	void fire();
	void move(float dx, float dy) { x = x + dx; y = y + dy; Sprite.setPosition(x, y); };

	sf::Rect<float> boundingBox = { 0,0,Width,Height };
	std::vector<Bullet> bullets;

	float x;
	float y;
	float rotation = 0;
	float HP = 2;
};