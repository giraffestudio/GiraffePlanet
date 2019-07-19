#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	float Width = 9;
	float Height = 37;
public:
	Bullet(float x_pos, float y_pos, float _velocity) : x(x_pos), y(y_pos), velocity(_velocity)	{};
	
	void setPosition(int newx, int newy);
	void update(float dt);
	float x;
	float y;

	
	sf::Rect<float> boundingBox = {0,0,Width,Height};
	float velocity;
};

