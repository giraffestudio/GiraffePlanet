#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class GameState
{

private:
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	sf::Music music;
	sf::Sprite Background;
	sf::RenderWindow* window;
	
	Player* player;
	ResourceMan* resources;

	sf::Clock enemyFireClock;
	float enemyFireRate = 2.0f;		// times per second

	int currentLevel = 1;

public:
	
	GameState( Player* pplayer, sf::RenderWindow* pwindow, ResourceMan* pResources )
	{
		player = pplayer;
		window = pwindow;
		resources = pResources;
	};

	void draw();
	void update( const float dt );
	void handleInput();
	void handleEnemiesAI( const float dt );
	void checkCollisions();
	void addBullet( Bullet::Owner owner, float const x, float const y, float const speed );
	void playerFire();
	void LoadLevel1();
};

