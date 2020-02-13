#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Animation
{
private:
	sf::Sprite* Sprite;

public:
	Animation( sf::Sprite* OwnerSprite ) { Sprite = OwnerSprite; };
	void AddRelativeMovement( sf::Vector2f movement );
	void update( const float dt );

	enum class AnimationType { NONE=0, MOVE=1, ROTATE=2, SCALE=3 };
	AnimationType Type = AnimationType::NONE;	

	sf::Vector2f relative_movement = { 0.f,0.f};
	float dest_rotation = 0;
	sf::Vector2f dest_scale = { 1.f,1.f };
	sf::Vector2f begin_scale = { 1.f,1.f };

	float duration = 0.f;	// animation duration in seconds
	float timer = 0.f;


};
