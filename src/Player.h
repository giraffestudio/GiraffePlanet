#pragma once
#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceMan.h"
#include "Bullet.h"
#include "ParticleSystem.h"
#include "Animation.h"

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

	float maxSpeed = 550.f;	//	px per sec
	float maxAccX = 400.f;
	float maxAccY = 360.f;
	float velocityX = 0.f;
	float velocityY = 0.f;
	float accX = 0.f;
	float accY = 0.f;
	float decX = 20.f;
	float decY = 20.f;
	float fireRate = 5.0f;		// times per sec
	unsigned int HP = 4;

	struct { bool left; bool right; bool front; bool back; } thrust = { false, false, false, false };

	std::vector<sf::Sprite> DamageSprites;
	std::vector<Bullet> bullets;
	ParticleSystem smoke = ParticleSystem(10000);

	std::vector<Animation> ani;

	void init(ResourceMan* pResources);
	void update(float dt);
	void setPosition(float newx, float newy);
	void fire();
};

