#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

    ParticleSystem( unsigned int MaxParticleCount );

    void setEmitter( sf::Vector2f position );
    void update( float elapsed );
    void addParticle( sf::Vector2f position, sf::Color Color, sf::Vector2f Velocity, float LifeTime );

private:

    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

    struct Particle
    {
        sf::Vector2f velocity;
        float lifetime;
    };

    void resetParticle( std::size_t index );

    std::vector<Particle> Particles;
    sf::VertexArray Vertices;
    float m_lifetime;
    sf::Vector2f m_emitter;
    float SpawnRate = 0.002f;
    float SpawnTimer = 0.f;
};