#pragma once
#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	void update(float dt);
	
	std::vector<sf::Texture> DamageTextures;
	sf::Texture Texture;
	std::vector<sf::Sprite> DamageSprites;
	sf::Sprite Sprite;

	float x=960;
	float y=900;
	float Width=112;
	float Height = 75;
	float maxSpeed = 550; // px for sec
	float velocityX = maxSpeed;
	float velocityY = 0;
	unsigned int HP = 4;

	sf::Rect<float>boundingBox = { 0,0,Width,Height };

	void setPosition(float newx, float newy);
};

