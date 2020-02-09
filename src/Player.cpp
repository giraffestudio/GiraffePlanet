#include "Player.h"
#include <memory>


void Player::init( ResourceMan* pResourceManager )
{
	resources = pResourceManager;
	
	Sprite = sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_orange.png" ) );
	Sprite.setOrigin( 56, 75 / 2 );
	Sprite.setPosition(x, y);

	DamageSprites.emplace_back( sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_damage1.png" ) ) );
	DamageSprites.emplace_back( sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_damage2.png" ) ) );
	DamageSprites.emplace_back( sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_damage3.png" ) ) );

	for (auto& ds : DamageSprites) ds.setOrigin(56, 75 / 2);

	smoke.setEmitter( sf::Vector2f( x, y ) );
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
	float moveY = dt * velocityY;
	float moveX = dt * velocityX;

	// set calculated position
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

	smoke.setEmitter( sf::Vector2f( x, y ) );
	smoke.update( dt );
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
	
	if ( (newy > Height/ 2.0f+10.0f ) && (newy < 1080.0f-Height/2.0f-10.0f) ) y = newy;
	
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
