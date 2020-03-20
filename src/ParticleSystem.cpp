#include "ParticleSystem.h"
#include <random>
#include <iostream>

constexpr auto M_PI = 3.14159265358979323846;

ParticleSystem::ParticleSystem( unsigned int ParticleCount )
{
    Particles.resize( ParticleCount );
    for ( auto& particle : Particles ) {
        particle.lifetime = 0.f;
        particle.velocity = { 0.f,0.f };
    }
    Vertices = sf::VertexArray( sf::PrimitiveType::Points, ParticleCount );  
    setEmitterPosition( { 0.f,0.f } );  
    setEmitterWidth( 1.f );  
}

void ParticleSystem::addParticle( sf::Color Color, sf::Vector2f Velocity, float LifeTime )
{
    float x_var=0.f;
    // find first dead particle
    for ( unsigned int i=0; i<Particles.size(); ++i )
    {
        if ( Particles[i].lifetime == 0 )
        {
            Particles[i].lifetime = LifeTime;
            Particles[i].velocity = Velocity;
            Vertices[i].color = Color;
            if ( EmitterWidth > 1 )
                {
                    x_var= static_cast <float> ( rand() ) / ( static_cast <float> ( RAND_MAX / EmitterWidth ) );
                };
            Vertices[i].position = sf::Vector2f( EmitterPosition.x + x_var, EmitterPosition.y );
            break;
        }
    }
    // if there is no particle dead - do not add new
}

void ParticleSystem::setEmitterPosition( sf::Vector2f Position)
{
    EmitterPosition = Position;
}

void ParticleSystem::setEmitterWidth( float Width )
{
    EmitterWidth = Width;
}

void ParticleSystem::setEmitterSpawnRate( float Rate )
{
    SpawnRate = Rate;
}

void ParticleSystem::setDirection( float Start, float End )
{
    DirStart = Start;
    DirEnd = End;
}

void ParticleSystem::setSpeed( float min, float max )
{
    MaxSpeed = max;
    MinSpeed = min;
}

void ParticleSystem::setColor( sf::Color BaseColor )
{
    Color = BaseColor;
}

void ParticleSystem::setParticleLifetime( float Lifetime )
{
    ParticleLifetime = Lifetime;
}

void ParticleSystem::update( float elapsed )
{
    if ( enabled == false ) return;
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen( rd() ); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> rnd_speed( MinSpeed, MaxSpeed );
    std::uniform_real_distribution<float> rnd_angle( DirStart, DirEnd );

    for ( std::size_t i = 0; i < Particles.size(); ++i )
    {
        // update the particle lifetime
        Particle& p = Particles[i];
        p.lifetime -= elapsed;

        
        if ( p.lifetime <= 0 ) // if the particle is dead
        {
            Particles[i].lifetime = 0;
        }
        else // update particle
        {
            // update the position of the corresponding vertex
            Vertices[i].position += p.velocity * elapsed;

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime / ParticleLifetime;
            Vertices[i].color.a = static_cast<sf::Uint8>( ratio * 255 );
        }      
    }

    CurrentEnabledTime += elapsed;
    if ( ( EnabledTime != -1 ) && ( CurrentEnabledTime >= EnabledTime ) )
    {
     
        return;
    }
    else
    {
        SpawnTimer += elapsed;
        if ( SpawnTimer >= SpawnRate )
        {
            // give a random velocity and lifetime to the particle
            int ParticlesToAdd = static_cast<int>( SpawnTimer / SpawnRate );
            for ( size_t i = 0; i < ParticlesToAdd; ++i )
            {
                float angle = rnd_angle( gen ) * 3.1415f / 180.f;
                float speed = rnd_speed( gen );
                sf::Vector2f velocity = sf::Vector2f( std::cos( angle ) * speed, std::sin( angle ) * speed );
                addParticle( Color, velocity, ParticleLifetime );
            }
            SpawnTimer = 0;
        }
    }
}

void ParticleSystem::enable( float EnabledForSec )
{
    enabled = true;
    EnabledTime = EnabledForSec;
}

void ParticleSystem::disable( void )
{
    enabled = false;
}

void ParticleSystem::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    if ( enabled == false ) return;
    // apply the transform
    states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    target.draw( Vertices, states );
}

void ParticleSystem::resetParticle( std::size_t index )
{
    /*// give a random velocity and lifetime to the particle
    float angle = (( 85+(std::rand() % 10 )) * 3.14f / 180.f);
    float speed = ( std::rand() % 50 ) + 50.f;
    m_particles[index].velocity = sf::Vector2f( std::cos( angle ) * speed, std::sin( angle ) * speed );
    m_particles[index].lifetime = 3;

    // reset the position of the corresponding vertex
    m_vertices[index].position = m_emitter;*/
}