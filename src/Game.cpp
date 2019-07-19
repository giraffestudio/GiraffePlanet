#include "Game.h"
#include <algorithm>

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))addBullet();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))player.setPosition(player.x+10, player.y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))player.setPosition(player.x-10, player.y);
		dt = clock.restart();
		Update(dt.asSeconds());
		Draw();
	}
}

void Game::Init()
{
	sf::VideoMode FullScreen = sf::VideoMode(1920, 1080, 32);
	sf::Uint32 WindowStyle = sf::Style::Fullscreen;
	Window.create(FullScreen, "Game" , WindowStyle);
	Window.setFramerateLimit(75);
	Window.setMouseCursorVisible(false);

	BulletTexture.loadFromFile("../res/PNG/Lasers/laserBlue03.png");
	BulletSprite.setTexture(BulletTexture);
	BulletSprite.setOrigin(4, 0);

	pew.loadFromFile("../res/Sound/Laser_1.wav");
	
	sound.setBuffer(pew);

}

bool isBulletOffScreen(Bullet testedBullet)
{
	return (testedBullet.y < 0);
}
void Game::Update(float dt)
{
	Bullets.erase( std::remove_if(Bullets.begin(), Bullets.end(), isBulletOffScreen), Bullets.end() );
	for (auto& bullet : Bullets)
	{
		bullet.update(dt);
	}
}

void Game::Draw()
{
	Window.clear(sf::Color::Black);
	
	for (auto& bullet : Bullets)
	{
		BulletSprite.setPosition(bullet.x, bullet.y);
		Window.draw(BulletSprite);
	}
	Window.draw(player.Sprite);
	Window.display();
}

void Game::addBullet()
{
	sound.play();
	Bullet newBullet;
	newBullet.setPosition(player.x, player.y);
	Bullets.push_back(newBullet);
}
