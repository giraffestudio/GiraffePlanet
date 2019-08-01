#include "Game.h"
#include <algorithm>
#include <random>

Game::~Game()
{
	delete level_1;
}

void Game::Init()
{
	// resourceMan.LoadSpriteSheetXML("../res/Spritesheet/sheet.xml");

	// When in debug mode do not use full screen - it sucks to switch back to IDE through task manager
#ifdef _DEBUG
	sf::VideoMode FullScreen = sf::VideoMode(1920, 1080, 32);
	sf::Uint32 WindowStyle = sf::Style::Resize;
#else
	sf::VideoMode FullScreen = sf::VideoMode(1920, 1080, 32);
	sf::Uint32 WindowStyle = sf::Style::Fullscreen;
#endif // _DEBUG
	
	window.create(FullScreen, "Game" , WindowStyle);
	window.setFramerateLimit(75);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	// Loading of textures
	spriteSheet.loadFromFile("../RES/SpriteSheet/sheet_cor.png");
	player.init(&spriteSheet);
	level_1 = new Level_1(&player, &window, &spriteSheet);
	level_1->Init();
	
	// Loading of sounds
	//* Game Over
	sbGameOver.loadFromFile("../res/Sound/GameOver_1.wav");
	// * Laser
	sbPlayerFire.loadFromFile("../res/Sound/Laser_1.wav");
	
	sound.setBuffer(sbPlayerFire);

}

void Game::Run()
{
	while (window.isOpen())
	{
		frameRenderTime = FrameClock.restart();
		level_1->handleInput();
		level_1->update(frameRenderTime.asSeconds());
		level_1->draw();
	}
}