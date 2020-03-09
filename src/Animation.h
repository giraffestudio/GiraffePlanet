#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Animation
{
private:
	sf::Sprite* Sprite;
	bool enabled = false;
	bool finished = false;

public:
	Animation( sf::Sprite* OwnerSprite, bool isEnabled = false ) { Sprite = OwnerSprite; enabled = isEnabled; };
	void AddMovement( sf::Vector2f movement, float duration_sec );
	void AddRotation( const float rotation_deg, float duration_sec );
	void update( const float dt );
	void enable() {	enabled = true; };
	void disable() { enabled = false; };
	bool isFinshed() { return finished; };

	enum class AnimationType { NONE=0, MOVE=1, ROTATE=2, SCALE=3, ALPHA=4 };
	AnimationType Type = AnimationType::NONE;	

	sf::Vector2f relative_movement = { 0.f,0.f};
	sf::Vector2f begin_position = { 0.f, 0.f };
	sf::Vector2f end_position = { 0.f, 0.f };
	sf::Vector2f dest_scale = { 1.f,1.f };
	sf::Vector2f begin_scale = { 1.f,1.f };

	float current_rotation = 0.f;
	float dest_rotation = 0.f;		// rotation to reach
	float begin_rotation = 0.f;

	float current_alpha = 0.f;		// current alpha
	float begin_alpha = 255.f;		// starting alpha
	float end_alpha = 255.f;		// alpha to reach
	float duration = 0.f;			// animation duration in seconds
	float timer = 0.f;				// animation timer


};
