#pragma once

#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

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
	sf::Clock FrameClock;	
	sf::Time dt;
	Player player;
	std::vector<Bullet> PlayerBullets;
	std::vector<Bullet> EnemyBullets;
	std::vector<Enemy> Enemies;
	void addBullet();

	sf::Texture spriteSheet;
	
	sf::Texture EnemyBulletTexture;
	sf::Sprite EnemyBulletSprite;
	
	sf::Texture PlayerBulletTexture;
	sf::Sprite PlayerBulletSprite;

	sf::SoundBuffer sbGameOver;
	sf::SoundBuffer sbPlayerFire;
	sf::Sound sound;
	
	sf::Clock EnemyFireClock;
	sf::Clock fireClock;
	sf::Time fireDt;
	double fireRate = 5; //  (Hz)

	void EnemyFire();

};