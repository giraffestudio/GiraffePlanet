#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(float _x, float _y) { x = _x; y = _y; };
	void update(float dt);

	float x;
	float y;
	float Width = 93;
	float Height = 84;
	float rotation = 0;
	float HP = 2;
	
	sf::Rect<float> boundingBox = { 0,0,Width,Height };
};