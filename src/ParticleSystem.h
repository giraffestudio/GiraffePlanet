#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

    ParticleSystem( unsigned int ParticleCount );

    void setEmitterPosition( sf::Vector2f Position);
    void setEmitterWidth( float Width );
    void setEmitterSpawnRate( float Rate );
    void setDirection( float Start, float End );
    void setSpeed( float min, float max );
    void setColor( sf::Color BaseColor );
    void setParticleLifetime( float Lifetime = 3.f);
    void update( float elapsed );
    void enable( float EnableForSec = -1 );  // -1 = enabled forever until disabled
    void disable( void );
    void addParticle( sf::Color Color, sf::Vector2f Velocity, float LifeTime );

private:

    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

    struct Particle
    {
        sf::Vector2f velocity = { 0.f,0.f };
        float lifetime = 0.f;
    };

    void resetParticle( std::size_t index );

    std::vector<Particle> Particles;
    sf::VertexArray Vertices;
    float ParticleLifetime = 3.f;
    sf::Vector2f EmitterPosition = { 0,0 };
    float EmitterWidth = 0.f;
    float SpawnRate = 0.005f;
    float SpawnTimer = 0.f;
    float DirStart = 0.f;
    float DirEnd = 360.f;
    float MinSpeed = 100;
    float MaxSpeed = 250;
    sf::Color Color = { 255,255,255,0 };
    bool enabled = false;
    float EnabledTime = 4.f;      // How long is the particle system to be active
    float CurrentEnabledTime = 0.f;    // Current PS timer
};