#include <random>
#include "Level_1.h"

void Level_1::Init()
{
	/*float enemies_rows = 3;
	float enemies_cols = 10;
	for (int row = 0; row < enemies_rows; ++row)
		for (int col = 0; col < enemies_cols; ++col)
		{
			enemies.emplace_back( Enemy( 100 + ( 1720.f / ( enemies_cols - 1 ) ) * static_cast<float>( col ), 100.0f + 150.0f * row, resources ) );
		}
	music.openFromFile( "../RES/sound/Droid.WAV" );
	music.play();

	Background.setTexture( resources->getBackground( "Black" ) );
	Background.setTextureRect( { 0, 0, 1920, 1080 } );*/
}

void Level_1::draw()
{
/*	window->draw( Background );
	 
	// draw our brave player
	window->draw(*player);
	
	// draw those filthy enemies
	for (auto& enemy : enemies)	window->draw(enemy);

	window->display();*/
}

void Level_1::update(const float dt)
{
	/*// update player (and his bullets as well)
	player->update(dt);
	
	handleEnemiesAI(dt);
	handleCollisions();

	// update bullets that still are with us
	for ( auto& bullet : Bullets )
	{
		bullet.update( dt );
	}*/
}

void Level_1::handleEnemiesAI( const float dt )
{
/*	if ( enemies.size() == 0 ) return;

	// handle enemies firing
	if ( enemyFireClock.getElapsedTime().asSeconds() >= 1.0f / enemyFireRate )
	{
		enemyFireClock.restart();
		constexpr int EnemiesShootingCount = 1;

		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen( rd() ); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> dis( 0, static_cast<int>( enemies.size() ) - 1 );

		for ( int i = 0; i < EnemiesShootingCount; ++i )
		{
			int random_index = dis( gen );
			enemies.at( random_index ).fire();
		}
	}

	// update enemies (and their bullets, too)
	for ( auto& enemy : enemies ) enemy.update( dt );
	*/
}

void Level_1::handleInput()
{
/*	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape) window->close();
		}
		if (event.type == sf::Event::Closed) window->close();
	}

	if (sf::Keyboard::isKeyPressed( sf::Keyboard::Space) ) playerFire();
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) player->thrust.left = true; else player->thrust.left=false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) player->thrust.right = true; else player->thrust.right = false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) player->thrust.back = true; else player->thrust.back = false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) player->thrust.front = true; else player->thrust.front = false;*/
}

void Level_1::playerFire()
{
	/*if ( player->fireClock.getElapsedTime().asSeconds() < 1.0f / player->fireRate ) return;

	addBullet( Bullet::Owner::PLAYER, player->x, player->y, 900.f );

	player->fireClock.restart();

	// play some  shitty sound
	resources->playSample( "Laser_1" );*/
}

void Level_1::handleCollisions()
{
	/*// player <-> enemy collisions
	for (auto& enemy : enemies)
		if (enemy.boundingBox.intersects(player->boundingBox) == true) window->close();
	
	// player bullets <-> enemy collision detection
	for (auto bullet = player->bullets.begin(); bullet != player->bullets.end(); ++bullet)
	{
 		for (std::vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
		{
			if (bullet->boundingBox.intersects(enemy->boundingBox) == true)
			{
				enemy->hit();
				if (enemy->HP == 0)
				{
					enemy = enemies.erase(enemy);
				}
				bullet = player->bullets.erase(bullet);
				break;
			}
		}
		if (bullet == player->bullets.end()) break;
	}

	// player <-> enemy bullets collision detection
	for(auto& enemy : enemies)
		for (auto bullet = enemy.bullets.begin(); bullet != enemy.bullets.end(); ++bullet)
		{
			if (bullet->boundingBox.intersects(player->boundingBox) == true)
			{
				//sound.setBuffer(sbGameOver);
				//sound.play();
				player->HP--;
				bullet = enemy.bullets.erase(bullet);
				if (player->HP == 0) window->close();
			}
			if (bullet == enemy.bullets.end()) break;
		}*/
}

void Level_1::addBullet( Bullet::Owner const owner, float const x, float const y, float const speed )
{
}