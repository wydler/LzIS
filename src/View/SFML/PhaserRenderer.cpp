#include "PhaserRenderer.hpp"


using namespace View::SFML;


void PhaserRenderer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	sf::CircleShape circle( 10.0f );
	circle.setOrigin( 10.0f, 10.0f );
	circle.setOutlineColor( sf::Color::White );
    circle.setOutlineThickness( 0 );
    circle.setFillColor( sf::Color( 165, 0, 215 ) );

    sf::RectangleShape rect( sf::Vector2f( 20, 3 ) );
    rect.setOrigin( 10.0, 15.0 );

	for( const Model::Phaser * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );

        if( m->getEnemy() )
        {
            sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f( m->getPosition().x, m->getPosition().y ), m->isPulseNeeded()?sf::Color( 0, 0, 255 ):sf::Color( 255, 0, 0 ) ),
                sf::Vertex(sf::Vector2f( m->getEnemy()->getPosition().x, m->getEnemy()->getPosition().y ), m->isPulseNeeded()?sf::Color( 0, 0, 255 ):sf::Color( 255, 0, 0 ) )
            };
            target.draw( line, 2, sf::Lines, states );
        }

        rect.setPosition( m->getPosition().x, m->getPosition().y );
        rect.setFillColor( sf::Color( 0, 255, 0 ) );
        rect.setSize( sf::Vector2f( m->getPulses() / 5.0 * 20.0, 3 ) );

        target.draw( rect, states );
        target.draw( circle, states );
	}
}
