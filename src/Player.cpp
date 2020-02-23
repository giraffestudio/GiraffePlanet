#include "Player.h"
#include <memory>


void Player::init( ResourceMan* pResourceManager )
{
	resources = pResourceManager;
	
	Sprite = sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_orange.png" ) );
	Sprite.setOrigin( 56, 75 / 2 );
	Sprite.setPosition(x, y);
	Sprite.setScale( { 3.f,3.f } );
	
	Animation IntroAnimation(&Sprite);
	IntroAnimation.Type = Animation::AnimationType::SCALE;
	IntroAnimation.duration = 1.f;
	IntroAnimation.dest_scale = { 1.f,1.f };
	IntroAnimation.begin_scale = { 20.f, 2.f};
	ani.push_back( IntroAnimation );

	IntroAnimation.Type = Animation::AnimationType::MOVE;
	IntroAnimation.duration = 3.f;
	IntroAnimation.relative_movement = { 100.f, 100.f };
	ani.push_back( IntroAnimation );

	DamageSprites.emplace_back( sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_damage1.png" ) ) );
	DamageSprites.emplace_back( sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_damage2.png" ) ) );
	DamageSprites.emplace_back( sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_damage3.png" ) ) );

	for (auto& ds : DamageSprites) ds.setOrigin(56, 75 / 2);

	smoke.setEmitterWidth( 10.f);
	smoke.setEmitterSpawnRate( 0.1f );
	smoke.setDirection( 85.f, 95.f );
	smoke.setSpeed( 50.f, 150.f );
	smoke.setColor( { 255, 100, 30, 255 } );
	smoke.enable();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// draw angel dust :)
	target.draw( smoke );
	
	// Draw player
	target.draw(Sprite, states);

	// Draw player damage
	//sf::RenderStates damageRenderStates = sf::BlendAlpha;
	if (HP < 4 && HP>0) target.draw( DamageSprites[ 3-HP ], states );

	// Draw player bullets
	for (auto& bullet : bullets)
	{
		target.draw(bullet);
	}	
}

void Player::update(float dt)
{
	// calculate movement
	if ( thrust.left ) {
		accX = maxAccX;
		velocityX += dt * accX;
	}

	if ( thrust.right ) {
		accX = -maxAccX;
		velocityX += dt * accX;
	}

	if ( thrust.front ) {
		accY = -maxAccY;
		velocityY += dt * accY;
	}

	if ( thrust.back ) {
		accY = maxAccY;
		velocityY += dt * accY;
	}
	
	if ( !( thrust.left && thrust.right ) )	// no left or right thrust engaged
	{
		bool sign_before = std::signbit( velocityX );
		accX = -std::copysignf( decX, velocityX);
		velocityX += dt * accX;
		if ( std::signbit( velocityX ) != sign_before ) // wyhamowa³ do zera
		{
			velocityX = 0;
		}
	}

	if ( !( thrust.front && thrust.back ) )	// no front or back thrust engaged
	{
		bool sign_before = std::signbit( velocityY );
		accY = -std::copysignf( decY, velocityY );
		velocityY += dt * accY;
		if ( std::signbit( velocityY ) != sign_before ) // wyhamowa³ do zera
		{
			velocityY = 0;
		}
	}
	
	float moveY = velocityY * dt;
	float moveX = velocityX * dt; 

	if ( ( velocityY != 0 ) || ( velocityX != 0 ) )
		smoke.setEmitterSpawnRate( 0.002f );
	else
		smoke.setEmitterSpawnRate( 0.05f );

	// set calculated position
	if ( ( x + moveX <= Width/2 ) || ( x + moveX >= 1920 - Width/2 ) )
	{ 
 		velocityX = 0;
		moveX = 0;
	}

	setPosition(x + moveX, y + moveY);

	boundingBox.left = x - 56;
	boundingBox.top = y - 75.0f / 2.f;

	// say goodbye to bullets that are off-screen
	auto isBulletOffScreen = [](Bullet testedBullet) { return ((testedBullet.y < 0) || (testedBullet.y > 1080)); };
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), isBulletOffScreen), bullets.end());

	// update bullets that still are with us
	for (auto& bullet : bullets)
	{
		bullet.update(dt);
	}

	smoke.setEmitterPosition( sf::Vector2f( x-5, y ) );
	smoke.update( dt );

	// handle animations
	for ( auto& a : ani)
	{
		a.update( dt );
	}
}


void Player::setPosition(float newx, float newy)
{
	if (newx > 1919 - Width / 2)
	{
		x = 1919 - Width / 2;
	}
	else
	{
		x = newx;
	}
	if (x < 56)
	{
		x = 56;
	}
	
	if ( ( newy > Height / 2.0f + 10.0f ) && ( newy < 1080.0f - Height / 2.0f - 10.0f ) ) y = newy;
	
	Sprite.setPosition(x, y);
	for( auto& ds : DamageSprites)
	{
		ds.setPosition(x, y);
	}
}

void Player::fire()
 {
	// if the time since last firing is too short then abort
    if (fireClock.getElapsedTime().asSeconds() < 1.0f / fireRate) return;

	// add new bullet to vector of player's bullets
 	bullets.emplace_back(x, y, 900.0f, resources, Bullet::Type::PLAYER_BULLET);

	// restart timer
	fireClock.restart();

	// play some  shitty sound
	resources->playSample("Laser_1");
}
