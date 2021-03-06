#include "Player.h"
#include "GameState.h"
#include <memory>


void Player::init( ResourceMan* pResourceManager )
{
	resources = pResourceManager;
	
	Sprite = sf::Sprite( resources->getSpriteSheet(), resources->getSpriteRect( "playerShip2_orange.png" ) );
	Sprite.setOrigin( 56, 75 / 2 );
	Sprite.setPosition(x, y);
	
	
	Animation IntroAnimation(&Sprite);
	/*IntroAnimation.Type = Animation::AnimationType::SCALE;
	IntroAnimation.duration = 0.3f;
	IntroAnimation.dest_scale = { 1.f,1.f };
	IntroAnimation.begin_scale = { 20.f, 2.f};
	animations.push_back( IntroAnimation );*/

	IntroAnimation.Type = Animation::AnimationType::ALPHA;
	IntroAnimation.AddAlpha(0.f, 255.f, 1.f);
	animations.push_back( IntroAnimation );

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
	if ( enabled == false ) return;
	
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
		if ( std::signbit( velocityX ) != sign_before ) // wyhamowa� do zera
		{
			velocityX = 0;
		}
	}

	if ( !( thrust.front && thrust.back ) )	// no front or back thrust engaged
	{
		bool sign_before = std::signbit( velocityY );
		accY = -std::copysignf( decY, velocityY );
		velocityY += dt * accY;
		if ( std::signbit( velocityY ) != sign_before ) // wyhamowa� do zera
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

	setPosition(Sprite.getPosition().x + moveX, Sprite.getPosition().y + moveY);

	boundingBox.left = x - 56;
	boundingBox.top = y - 75.0f / 2.f;

	smoke.setEmitterPosition( sf::Vector2f( x-5, y ) );
	smoke.update( dt );

	// delete animation that are finished
	auto isAnimationFinished = []( Animation testedAnimation ) { return testedAnimation.isFinshed(); };
	animations.erase( std::remove_if( animations.begin(), animations.end(), isAnimationFinished ), animations.end() );

	// handle animations
	for ( auto& a : animations)
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
 	bullets.emplace_back(x, y, 900.0f, resources, Bullet::Owner::PLAYER);
	

	// restart timer
	fireClock.restart();

	// play some  shitty sound
	resources->playSample("Laser_1");
}

void Player::enable()
{
	enabled = true;
	for ( auto& animation : animations ) animation.enable();
}

void Player::disable()
{
	enabled = false;
	for ( auto& animation : animations ) animation.disable();
}
