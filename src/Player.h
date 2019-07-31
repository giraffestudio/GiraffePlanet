#pragma once
#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
private:
	sf::IntRect spriteSheetSubRect = { 112,716,112,75 };
	sf::Sprite Sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	Player();
	void setTexture(sf::Texture &spriteSheet);
	
	void update(float dt);
	
	std::vector<sf::Texture> DamageTextures;
	
	std::vector<sf::Sprite> DamageSprites;
	

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

