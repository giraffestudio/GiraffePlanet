#pragma once

#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Bullet.h"

class Game
{
public:
	void Run();
	void Init();
	sf::RenderWindow Window;
	sf::Mouse mouse;

private:
	void Update(float dt);
	void Draw();
	sf::Clock clock;	
	sf::Time dt;
	Player player;
	std::vector<Bullet> Bullets;
	void addBullet();

	sf::Texture BulletTexture;
	sf::Sprite BulletSprite;
	
	sf::SoundBuffer pew;
	sf::Sound sound;
	

};