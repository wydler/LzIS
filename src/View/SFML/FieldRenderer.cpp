#include "FieldRenderer.hpp"

#include <iostream>


using namespace View::SFML;


void FieldRenderer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
    sf::CircleShape hexagon( 20, 6 );
    hexagon.setScale( 1, 1 );
    hexagon.setOrigin( 20, 20 );
    hexagon.setFillColor( sf::Color( 0, 124, 16 ) );

    for( const Model::AField2D * m : this->getModels() )
    {
        switch( m->getState() )
        {
        case FieldState::IDLE:
            hexagon.setFillColor( sf::Color( 0, 124, 16 ) );
            break;
        case FieldState::HOVER:
            hexagon.setFillColor( sf::Color( 0, 255, 16 ) );
            break;
        case FieldState::ACTIVE:
            hexagon.setFillColor( sf::Color( 0, 124, 255 ) );
            break;
        }
        hexagon.setPosition( m->getPosition().x, m->getPosition().y );

        target.draw( hexagon, states );
    }
}
