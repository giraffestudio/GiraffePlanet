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
	ResourceMan* resources;

	GameState(Player* pplayer, sf::RenderWindow* pwindow, ResourceMan* pResources)
	{
		player = pplayer;
		window = pwindow;
		resources = pResources;
	}

	virtual void draw() = 0 ;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;

};

