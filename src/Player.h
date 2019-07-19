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
	std::vector<sf::Sprite> DamageSptites;
	sf::Sprite Sprite;

	double x=960;
	double y=900;
	double Width=112;
	double Height = 75;
	double maxSpeed = 550; // px for sec
	double velocityX = maxSpeed;
	double velocityY = 0;
	double HP = 4;

	sf::Rect<float>boundingBox = { 0,0,Width,Height };

	void setPosition(double newx, double newy);
};

