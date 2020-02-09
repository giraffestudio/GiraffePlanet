#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem( unsigned int MaxParticleCount )
{
    Particles.resize( MaxParticleCount );
    Vertices = sf::VertexArray( sf::Points, MaxParticleCount );
    m_lifetime = 5.f ;
    m_emitter = sf::Vector2f( 0.f, 0.f );
}

void ParticleSystem::addParticle( sf::Vector2f Position, sf::Color Color, sf::Vector2f Velocity, float LifeTime )
{
    
    // find first dead particle
    for ( unsigned int i=0; i<Particles.size(); ++i )
    {
        if ( Particles[i].lifetime == 0 )
        {
            Particles[i].lifetime = LifeTime;
            Particles[i].velocity = Velocity;
            Vertices[i].color = Color;
            Vertices[i].position = Position;
            break;
        }
    }
    // if there is no particle dead - do not add new


}

void ParticleSystem::setEmitter( sf::Vector2f position )
{
    m_emitter = position;
}

void ParticleSystem::update( float elapsed )
{
    for ( std::size_t i = 0; i < Particles.size(); ++i )
    {
        // update the particle lifetime
        Particle& p = Particles[i];
        p.lifetime -= elapsed;

        // if the particle is dead, respawn it
        if ( p.lifetime <= 0 ) Particles[i].lifetime = 0;

        // update the position of the corresponding vertex
        Vertices[i].position += p.velocity * elapsed;

        // update the alpha (transparency) of the particle according to its lifetime
        float ratio = p.lifetime / m_lifetime;
        Vertices[i].color.a = static_cast<sf::Uint8>( ratio * 255 );
    }

    SpawnTimer += elapsed;
    if ( SpawnTimer >= SpawnRate )
    {
        // give a random velocity and lifetime to the particle
        int ParticlesToAdd = SpawnTimer / SpawnRate;
        for ( size_t i = 0; i < ParticlesToAdd; ++i )
        {
            float angle =  ( 85 + ( std::rand()/((RAND_MAX+1u)/10 ))) * 3.14f / 180.f ;
            float speed = ( std::rand() % 50 ) + 50.f;
            sf::Vector2f velocity = sf::Vector2f( std::cos( angle ) * speed, std::sin( angle ) * speed );
            addParticle( m_emitter, sf::Color( 0, 255, 100, 255 ), velocity, 5.f );
        }
        SpawnTimer = 0;
     }



}

void ParticleSystem::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
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