#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceMan.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Level_1 :	public GameState
{
private:
	sf::Clock enemyFireClock;
	float enemyFireRate = 2.0f;		// times per second
	sf::Music music;
	sf::Sprite Background;
	
	std::vector<Bullet> Bullets;
	std::vector<Enemy> enemies;


public:
	Level_1( Player* pplayer, sf::RenderWindow* pwindow, ResourceMan* pResources ) : GameState( pplayer, pwindow, pResources ) {};

	void Init();
	virtual void draw();
	virtual void update(const float dt);
	void handleEnemiesAI( const float dt );
	virtual void handleInput();
	void handleCollisions();
	void addBullet( Bullet::Owner owner, float const x, float const y, float const speed );
	void playerFire();
};

