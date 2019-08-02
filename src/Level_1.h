#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceMan.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"

class Level_1 :	public GameState
{
private:
	sf::Clock enemyFireClock;
	float enemyFireRate = 2.0f;		// times per second

public:
	Level_1(Player* pplayer, sf::RenderWindow* pwindow, ResourceMan* pResources) : GameState (pplayer, pwindow, pResources) {};

	void Init();
	virtual void draw();
	virtual void update(const float dt);
	virtual void handleInput();
	void handleCollisions();

	std::vector<Enemy> Enemies;
};

