#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceMan.h"

class Bullet : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	ResourceMan* resources;

public:
	enum class Owner { PLAYER = 1, ENEMY = 2 };
	float x;
	float y;
	float velocity;
	float Width = 9;
	float Height = 37;
	sf::Rect<float> boundingBox = { 0,0,Width,Height };
	sf::Sprite Sprite;
	Owner owner;

	Bullet(float x_pos, float y_pos, float _velocity, ResourceMan* pResources, Owner bulletOwner);
	void setPosition(float newx, float newy);
	void update(float dt);
	sf::Sprite getSprite() { return Sprite; };
};

