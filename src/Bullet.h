#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	enum Type { PLAYER_BULLET, ENEMY_BULLET};
	float x;
	float y;
	float velocity;
	float Width = 9;
	float Height = 37;
	sf::Rect<float> boundingBox = { 0,0,Width,Height };
	sf::Sprite Sprite;
	
	Bullet(float x_pos, float y_pos, float _velocity, sf::Texture* spriteSheet, Type bulleType);
	void setPosition(float newx, float newy);
	void update(float dt);
};

