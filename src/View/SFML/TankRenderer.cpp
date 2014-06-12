#include "TankRenderer.hpp"


using namespace View::SFML;


void TankRenderer::draw() const
{
    sf::RectangleShape rect( sf::Vector2f( 20, 3 ) );
    rect.setOrigin( 10.0, 15.0 );
    rect.setOutlineThickness( 1.0 );
    rect.setOutlineColor( sf::Color( 0, 0, 0, 127 ) );

    sf::CircleShape circle( 10 );
    circle.setFillColor( sf::Color( 0, 0, 255 ) );
    circle.setOrigin( 10, 10 );

    sf::ConvexShape convex;
    convex.setPointCount(4);
    convex.setOutlineColor( sf::Color( 0, 255, 0 ) );
    convex.setOutlineThickness( 1 );

    for( const Model::Tank * m : this->getModels() )
    {
        switch( m->getState() )
        {
        case LifeState::SPAWNING:
            break;
        case LifeState::ALIVE:
            circle.setPosition( m->getPosition().x, m->getPosition().y );

            rect.setPosition( m->getPosition().x, m->getPosition().y );
            rect.setFillColor( sf::Color( 255, 0, 0 ) );
            rect.setSize( sf::Vector2f( m->getLife() / 100.0 * 20.0, 3 ) );

            convex.setPoint( 0, sf::Vector2f( m->getMinCorner().x, m->getMinCorner().y ) );
            convex.setPoint( 1, sf::Vector2f( m->getMaxCorner().x, m->getMinCorner().y ) );
            convex.setPoint( 2, sf::Vector2f( m->getMaxCorner().x, m->getMaxCorner().y ) );
            convex.setPoint( 3, sf::Vector2f( m->getMinCorner().x, m->getMaxCorner().y ) );

            this->window.draw( convex );
            this->window.draw( circle );
            this->window.draw( rect );
            break;
        case LifeState::DYING:
            break;
        case LifeState::DEAD:
            break;
        }
    }
}
