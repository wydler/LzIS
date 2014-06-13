#include "TankRenderer.hpp"


using namespace View::SFML;


void EnemyRenderer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
    sf::RectangleShape life( sf::Vector2f( 20, 3 ) );
    life.setOrigin( 10.0, 15.0 );
    life.setOutlineThickness( 1.0 );
    life.setOutlineColor( sf::Color( 0, 0, 0, 127 ) );

    sf::CircleShape body( 10, 3 );
    body.setFillColor( sf::Color( 255, 0, 0 ) );
    body.setOrigin( 10, 10 );

    for( const Model::Tank * m : this->getModels() )
    {
        switch( m->getState() )
        {
        case LifeState::SPAWNING:
            break;
        case LifeState::ALIVE:
            body.setPosition( m->getPosition().x, m->getPosition().y );

            life.setPosition( m->getPosition().x, m->getPosition().y+22 );
            life.setFillColor( sf::Color( 255, 0, 0 ) );
            life.setSize( sf::Vector2f( m->getLife() / 100.0 * 20.0, 3 ) );

            target.draw( body, states );
            target.draw( life, states );
            break;
        case LifeState::DYING:
            break;
        case LifeState::DEAD:
            break;
        }
    }
}
