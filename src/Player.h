#pragma once
#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceMan.h"
#include "Bullet.h"
#include "ParticleSystem.h"

class Player : public sf::Drawable
{
private:
	ResourceMan* resources = nullptr;
	
	sf::Sprite Sprite;
	sf::Clock fireClock;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	float Width = 112.0f;
	float Height = 75.0f;

	sf::Rect<float>boundingBox = { 0,0,Width,Height };		// Watch for member initialization order !
	
	float x = 960;
	float y = 900;

	float maxSpeed = 550;	//	px per sec
	float velocityX = maxSpeed;
	float velocityY = 0;
	float fireRate = 5.0f;		// times per sec
	unsigned int HP = 4;

	std::vector<sf::Sprite> DamageSprites;
	std::vector<Bullet> bullets;
	ParticleSystem smoke = ParticleSystem(10000);

	void init(ResourceMan* pResources);
	void update(float dt);
	void setPosition(float newx, float newy);
	void fire();
};

