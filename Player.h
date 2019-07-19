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
	
	sf::Texture Texture;
	sf::Sprite Sprite;
	float x=960;
	float y=900;
	float Width=112;
	void setPosition(float newx, float newy);
};

