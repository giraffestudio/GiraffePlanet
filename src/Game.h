#pragma once

#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Level_1.h"
#include "ResourceMan.h"

class Game
{
	//friend class GameState;

public:
	~Game();
	void Run();
	void Init();
	sf::RenderWindow window;
	sf::Mouse mouse;

private:
	
	ResourceMan resources;

	sf::Clock FrameClock;
	sf::Time frameRenderTime;

	Player player;
	Level_1* level_1 = nullptr;

};