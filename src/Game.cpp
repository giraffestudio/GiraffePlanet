#include "Game.h"
#include <algorithm>
#include <random>

void Game::Run()
{
	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
	
				if (event.key.code == sf::Keyboard::Escape) Window.close();
				if (event.key.code == sf::Keyboard::Space) addBullet();
			}
			if (event.type == sf::Event::Closed) Window.close();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) addBullet();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.velocityX = player.maxSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.velocityX = -player.maxSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.velocityY = player.maxSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.velocityY = -player.maxSpeed;
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == false) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == false)) player.velocityX = 0;
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == false) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false)) player.velocityY = 0;

		dt = FrameClock.restart();
		EnemyFire();
		Update(dt.asSeconds());
		Draw();
	}
}

void Game::EnemyFire()
{
	if (EnemyFireClock.getElapsedTime().asSeconds() < 0.25) return;
	EnemyFireClock.restart();
	
	constexpr int EnemiesShootingCount = 1;
	std::vector<Enemy> ShootingEnemies;

	std::sample(Enemies.begin(), Enemies.end(), std::back_inserter(ShootingEnemies), EnemiesShootingCount, std::mt19937{ std::random_device{}() });

	for (auto& enemy : ShootingEnemies)
	{
		EnemyBullets.emplace_back(Bullet(enemy.x, enemy.y, -700));
	}
}

void Game::Init()
{
	sf::VideoMode FullScreen = sf::VideoMode(1920, 1080, 32);
	sf::Uint32 WindowStyle = sf::Style::Fullscreen;
	Window.create(FullScreen, "Game" , WindowStyle);
	Window.setFramerateLimit(75);
	Window.setVerticalSyncEnabled(true);
	Window.setMouseCursorVisible(false);

	// Loading of textures
	// * Bullet
	EnemyBulletTexture.loadFromFile("../res/PNG/Lasers/laserRed03.png");
	EnemyBulletSprite.setTexture(EnemyBulletTexture);
	EnemyBulletSprite.setOrigin(4.5, 0);
	EnemyBulletTexture.setSmooth(true);
	
	PlayerBulletTexture.loadFromFile("../res/PNG/Lasers/laserBlue03.png");
	PlayerBulletSprite.setTexture(PlayerBulletTexture);
	PlayerBulletSprite.setOrigin(4.5, 0);
	PlayerBulletTexture.setSmooth(true);

	// * Enemies
	EnemyTexture.loadFromFile("../res/PNG/Enemies/enemyGreen1.png");
	EnemySprite.setTexture(EnemyTexture);
	EnemySprite.setOrigin(46.5, 42);
	EnemyTexture.setSmooth(true);

	// Loading of sounds
	//* Game Over
	sbGameOver.loadFromFile("../res/Sound/GameOver_1.wav");
	// * Laser
	sbPlayerFire.loadFromFile("../res/Sound/Laser_1.wav");
	
	sound.setBuffer(sbPlayerFire);

	float enemies_rows = 4;
	float enemies_cols = 16;
	  for (int row = 0; row < enemies_rows; ++row)
			for (int col = 0; col < enemies_cols; ++col)
		{
			Enemies.emplace_back(Enemy(100+(1720.f/(enemies_cols-1))*static_cast<float>(col), 100.0f+150.0f*row));
		}
}

void Game::Update(float dt)
{
	auto isBulletOffScreen = [](Bullet testedBullet) { return ( (testedBullet.y < 0) || (testedBullet.y>1080 )); };
	PlayerBullets.erase( std::remove_if(PlayerBullets.begin(), PlayerBullets.end(), isBulletOffScreen), PlayerBullets.end() );
	EnemyBullets.erase(std::remove_if(EnemyBullets.begin(), EnemyBullets.end(), isBulletOffScreen), EnemyBullets.end());

	player.update(dt);

	for (auto& enemy : Enemies)
	{
		enemy.update(dt);
		// Player - enemy collision detection
		if (enemy.boundingBox.intersects(player.boundingBox) == true)
		{
			Window.close();
		}
	}
	
	// Enemy - Player bullets collision detection
	for (auto bullet=PlayerBullets.begin(); bullet!=PlayerBullets.end(); ++bullet)
	{
		bullet->update(dt);
		for (std::vector<Enemy>::iterator enemy=Enemies.begin(); enemy!=Enemies.end(); ++enemy)
		{
			
			if (bullet->boundingBox.intersects(enemy->boundingBox) == true)
			{
				enemy->rotation += 15-rand()%30;
				enemy->HP--;
				if (enemy->HP == 0)
				{
					enemy = Enemies.erase(enemy);
					
				}
				bullet = PlayerBullets.erase(bullet);
				break;
			}			
		}
		if (bullet == PlayerBullets.end()) break;
	}
	
	// Player - Enemy bullets collision detection
	for (auto bullet = EnemyBullets.begin(); bullet != EnemyBullets.end(); ++bullet)
	{
		bullet->update(dt);
		if (bullet->boundingBox.intersects(player.boundingBox) == true)
		{
			sound.setBuffer(sbGameOver);
			sound.play();
			player.HP--;
			bullet = EnemyBullets.erase(bullet);
			if (player.HP == 0) Window.close();
		}
	}
}

void Game::Draw()
{
	Window.clear(sf::Color::Black);
	
	for (auto& enemy : Enemies)
	{
		EnemySprite.setPosition(enemy.x, enemy.y);
		EnemySprite.setRotation(enemy.rotation);
		Window.draw(EnemySprite);
	}

	for (auto& bullet : PlayerBullets)
	{
		PlayerBulletSprite.setPosition(bullet.x, bullet.y);
		Window.draw(PlayerBulletSprite);
	}
	
	for (auto& bullet : EnemyBullets)
	{
		EnemyBulletSprite.setPosition(bullet.x, bullet.y);
		Window.draw(EnemyBulletSprite);
	}

	Window.draw(player.Sprite);
	if (player.HP < 4 && player.HP>0) Window.draw( player.DamageSprites[ 3-player.HP ] );
	Window.display();
}

void Game::addBullet()
{
	fireDt = fireClock.getElapsedTime();

	if (fireDt.asSeconds() < 1.0f / fireRate) return;
	sound.setBuffer(sbPlayerFire);
	sound.play();
	
	PlayerBullets.emplace_back(Bullet(player.x, player.y,900));
	fireDt = fireClock.restart();
}
