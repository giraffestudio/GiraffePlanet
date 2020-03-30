#include "GameState.h"
#include "Text.h"
#include "Collision.h"
#include <random>


void GameState::draw()
{
	// draw background
	window->draw( Background );

	// draw our brave player
	window->draw( *player );

	// draw those filthy enemies
	for ( auto& enemy : enemies ) window->draw( enemy );
	for ( auto& bullet : bullets ) window->draw( bullet );

	window->display();
}

void GameState::update( const float dt )
{
	// update player (and his bullets as well)
	player->update( dt );

	handleEnemiesAI( dt );
	checkCollisions();

	// say goodbye to bullets that are off-screen
	auto isBulletOffScreen = []( Bullet testedBullet ) { return ( ( testedBullet.y < 0 ) || ( testedBullet.y > 1080 ) ); };
	bullets.erase( std::remove_if( bullets.begin(), bullets.end(), isBulletOffScreen ), bullets.end() );

	// update bullets that still are with us
	for ( auto& bullet : bullets )
	{
		bullet.update( dt );
	}
}

void GameState::handleInput()
{
	sf::Event event;
	while ( window->pollEvent( event ) )
	{
		if ( event.type == sf::Event::KeyPressed )
		{
			if ( event.key.code == sf::Keyboard::Escape ) window->close();
		}
		if ( event.type == sf::Event::Closed ) window->close();
	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) playerFire();
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) player->thrust.left = true; else player->thrust.left = false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) player->thrust.right = true; else player->thrust.right = false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) player->thrust.back = true; else player->thrust.back = false;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) player->thrust.front = true; else player->thrust.front = false;
}

void GameState::handleEnemiesAI( const float dt )
{
	if ( enemies.size() == 0 ) return;

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
			addBullet(Bullet::Owner::ENEMY,enemies.at( random_index ).x, enemies.at( random_index ).y,-500.f);
		}
	}

	// update enemies (and their bullets, too)
	for ( auto& enemy : enemies ) enemy.update( dt );
}

void GameState::checkCollisions()
{
	// player <-> enemy collisions
	for ( auto& enemy : enemies )
		if ( Collision::PixelPerfectTest( player->getSprite(), enemy.getSprite(), 0u, resources->getBitmask() )) window->close();
		

	// player bullets <-> enemy collision detection
	for ( auto bullet = bullets.begin(); bullet!=bullets.end(); ++bullet )
	{
		switch ( bullet->owner )
		{
			case Bullet::Owner::PLAYER:
					for ( std::vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy )
					{
						if(Collision::PixelPerfectTest( bullet->getSprite(), enemy->getSprite(), 0u, resources->getBitmask()) )
						{
							enemy->hit();
							if ( enemy->HP == 0 )
							{
								enemy = enemies.erase( enemy );
							}
							bullet = bullets.erase( bullet );
							break;
						}
					}
					break;

			case Bullet::Owner::ENEMY:
					if( Collision::PixelPerfectTest(bullet->getSprite(), player->getSprite(), 0, resources->getBitmask()) )		
					{
						//sound.setBuffer(sbGameOver);
						//sound.play();
						player->HP--;
						bullet = bullets.erase( bullet );
						if ( player->HP == 0 ) window->close();
					}
					break;
		}
		if ( bullet == bullets.end() ) break;
	}
}

void GameState::addBullet( Bullet::Owner owner, float const x, float const y, float const speed )
{
	bullets.emplace_back( x, y, speed, resources, owner );
}

void GameState::playerFire()
{
	if ( player->fireClock.getElapsedTime().asSeconds() < 1.0f / player->fireRate ) return;

	addBullet( Bullet::Owner::PLAYER, player->x, player->y, 900.f );

	player->fireClock.restart();

	// play some  shitty sound
	resources->playSample( "Laser_1" );
}

void GameState::LoadLevel1()
{
	float enemies_rows = 3;
	float enemies_cols = 10;
	for ( int row = 0; row < enemies_rows; ++row )
		for ( int col = 0; col < enemies_cols; ++col )
		{
			enemies.emplace_back( Enemy( 100 + ( 1720.f / ( enemies_cols - 1 ) ) * static_cast<float>( col ), 100.0f + 150.0f * row, resources ) );
		}
	music.openFromFile( "../RES/sound/Droid.WAV" );
	music.play();

	Background.setTexture( resources->getBackground( "Black" ) );
	Background.setTextureRect( { 0, 0, 1920, 1080 } );

	LevelIntro();

	// enable player
	player->enable();

	// enable enemies
	for ( auto& enemy : enemies ) { enemy.enable(); };
}

void GameState::LevelIntro()
{
	texts.emplace_back( Text( resources->getFont( "Atari" ), 80 ,"Level One", static_cast<size_t>( Text::Alignement::HORIZONTAL_CENTER ) | static_cast<size_t>( Text::Alignement::VERTICAL_CENTER ) ));
	texts.emplace_back( Text( resources->getFont( "HelveticaNeueLTPro-LtCn" ), 40, "The insertion planet", static_cast<size_t>( Text::Alignement::HORIZONTAL_CENTER ), { 0,650 } ) );

	Animation AlphaAni(texts[0].getSprite(),true);
	AlphaAni.AddAlpha( 0.f, 255.f, 5.8f );
	
	texts[0].animations.push_back( AlphaAni );

	Animation SecAni( texts[1].getSprite(), true );
	SecAni.AddAlpha( 0.f, 255.f, 5.8f );
	texts[1].animations.push_back( SecAni );

	sf::Clock ck;
	sf::Clock frameClock;
	sf::Time dt;
	
	frameClock.restart();
	while ( ck.getElapsedTime().asSeconds() < 5.8 ) 
	{
		dt = frameClock.restart();
		texts[0].animations[0].update( dt.asSeconds() );
		texts[1].animations[0].update( dt.asSeconds() );

		window->clear();
		window->draw( texts[0] );
		window->draw( texts[1] );
		window->display();	
	}

	
	texts[0].animations.clear();
	texts[1].animations.clear();
	
	AlphaAni.AddAlpha( 255.f, 0.f, 5.8f );
	AlphaAni.timer = 0.f;
	texts[0].animations.push_back( AlphaAni );

	SecAni.AddAlpha( 255.f, 0.f, 5.8f );
	SecAni.timer = 0.f;
	texts[1].animations.push_back( SecAni );

	frameClock.restart();
	while ( ck.getElapsedTime().asSeconds() < 5.8f*2 )
	{
		dt = frameClock.restart();
		texts[0].animations[0].update( dt.asSeconds() );
		texts[1].animations[0].update( dt.asSeconds() );

		window->clear();
		window->draw( texts[0] );
		window->draw( texts[1] );
		window->display();
	}
}