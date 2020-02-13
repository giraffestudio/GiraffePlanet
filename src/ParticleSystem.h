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
    void update( float elapsed );
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
    float DefaultLifetime = 3.f;
    sf::Vector2f EmitterPosition = { 0,0 };
    float EmitterWidth = 0.f;
    float SpawnRate = 0.005f;
    float SpawnTimer = 0.f;
};