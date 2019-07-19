#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	void setPosition(float newx, float newy);
	void update(float dt);
	
	float x = 666;
	float y = 1000;
	
private:
	float velocity = 600;



};

