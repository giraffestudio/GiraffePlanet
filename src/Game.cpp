#include "Game.h"
#include <algorithm>
#include <random>

Game::~Game()
{
	delete level_1;
}

void Game::Init()
{
	resources.LoadResources();

	// When in debug mode do not use full screen - it sucks to switch back to IDE through task manager
#ifdef _DEBUG
	sf::VideoMode FullScreen = sf::VideoMode( 1920, 1080, 32 );
	sf::Uint32 WindowStyle = sf::Style::Resize;
#else
	sf::VideoMode FullScreen = sf::VideoMode( 1920, 1080, 32 );
	sf::Uint32 WindowStyle = sf::Style::Fullscreen;
#endif // _DEBUG

	window.create( FullScreen, "Game", WindowStyle );
	window.setFramerateLimit( 75 );
	window.setVerticalSyncEnabled( true );
	window.setMouseCursorVisible( false );

	player.init( &resources );
	level_1 = new Level_1( &player, &window, &resources );
	level_1->Init();
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