#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"

class GameState
{

private:

public:
	Player* player;
	sf::RenderWindow* window;
	sf::Texture* spriteSheet;

	GameState(Player* pplayer, sf::RenderWindow* pwindow, sf::Texture* pspriteSheet)
	{
		player = pplayer;
		window = pwindow;
		spriteSheet = pspriteSheet;
	}

	virtual void draw() = 0 ;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;

};

