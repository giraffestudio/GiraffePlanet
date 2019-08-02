#include <random>
#include "Level_1.h"

void Level_1::Init()
{
	float enemies_rows = 4;
	float enemies_cols = 12;
	for (int row = 0; row < enemies_rows; ++row)
		for (int col = 0; col < enemies_cols; ++col)
		{
			Enemies.emplace_back( Enemy( 100 + ( 1720.f / ( enemies_cols - 1 ) ) * static_cast<float>( col ), 100.0f + 150.0f * row, resources ) );
		}
}

void Level_1::draw()
{
	window->clear(sf::Color::Black);

	// draw our brave player
	window->draw(*player);
	
	// draw those filthy enemies
	for (auto& enemy : Enemies)	window->draw(enemy);

	window->display();
}

void Level_1::update(const float dt)
{
	// update player (and his bullets as well)
	player->update(dt);

	// handle enemies firing
	if (enemyFireClock.getElapsedTime().asSeconds() >= 1.0f / enemyFireRate)
	{
		enemyFireClock.restart();
		constexpr int EnemiesShootingCount = 1;

		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> dis(0, static_cast<int>(Enemies.size())-1);

		for (int i = 0; i < EnemiesShootingCount; ++i)
		{
			int random_index = dis(gen);
			Enemies.at(random_index).fire();
		}
	}
	
	// update enemies (and their bullets, too)
	for (auto& enemy : Enemies) enemy.update(dt);

	handleCollisions();
}

void Level_1::handleInput()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape) window->close();
		}
		if (event.type == sf::Event::Closed) window->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) player->fire();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player->velocityX = player->maxSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player->velocityX = -player->maxSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player->velocityY = player->maxSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player->velocityY = -player->maxSpeed;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == false) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == false)) player->velocityX = 0;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == false) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false)) player->velocityY = 0;
	
}

void Level_1::handleCollisions()
{
	// player <-> enemy collisions
	for (auto& enemy : Enemies)
		if (enemy.boundingBox.intersects(player->boundingBox) == true) window->close();
	
	// player bullets <-> enemy collision detection
	for (auto bullet = player->bullets.begin(); bullet != player->bullets.end(); ++bullet)
	{
 		for (std::vector<Enemy>::iterator enemy = Enemies.begin(); enemy != Enemies.end(); ++enemy)
		{
			if (bullet->boundingBox.intersects(enemy->boundingBox) == true)
			{
				enemy->rotation += 15 - rand() % 30;
				enemy->move(0,-10);
				enemy->HP--;
				if (enemy->HP == 0)
				{
					enemy = Enemies.erase(enemy);
				}
				bullet = player->bullets.erase(bullet);
				break;
			}
		}
		if (bullet == player->bullets.end()) break;
	}

	// player <-> enemy bullets collision detection
	for(auto& enemy : Enemies)
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
		}
}