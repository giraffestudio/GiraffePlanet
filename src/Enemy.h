#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceMan.h"
#include "Bullet.h"
#include "Animation.h"
#include "ParticleSystem.h"

class Enemy : public sf::Drawable
{
private:	
	ResourceMan* resources;
	
	float Width = 93.0f;
	float Height = 84.0f;
	bool enabled = false;

	sf::IntRect ssRect_green = { 425, 552, 93, 84 };		// Watch for member initialization order !
	sf::Sprite Sprite;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Animation> animations;

	ParticleSystem debris = ParticleSystem( 3500 );

public:
	Enemy(float x_pos, float y_pos, ResourceMan* pResources);
	void update(float dt);
	void fire();
	void move(float dx, float dy) { x = x + dx; y = y + dy; Sprite.setPosition(x, y); };
	void hit();
	void enable();
	void disable();

	sf::Rect<float> boundingBox = { 0,0,Width,Height };

	float x;
	float y;
	float rotation = 0;
	float HP = 2;
};