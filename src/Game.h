#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameState.h"
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
	sf::ContextSettings Settings;
private:
	
	ResourceMan resources;

	sf::Clock FrameClock;
	sf::Time frameRenderTime;
	sf::Event event;

	Player player;
	GameState* gamestate = nullptr;

};