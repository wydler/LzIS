#include "PhaserRenderer.hpp"


using namespace View::SFML;


void PhaserRenderer::draw() const
{
	sf::CircleShape circle( 10.0f );
	circle.setOrigin( 10.0f, 10.0f );
	circle.setOutlineColor( sf::Color::White );
	circle.setOutlineThickness( 2.0f );

    sf::CircleShape radius( 100.0f );
    radius.setOrigin( 100.0f, 100.0f );
	radius.setOutlineColor( sf::Color( 255, 0, 0, 100 ) );
	radius.setOutlineThickness( 1.0f );
	radius.setFillColor( sf::Color( 0, 255, 0, 0 ) );

    sf::ConvexShape convex;
    convex.setPointCount(4);
    convex.setOutlineColor( sf::Color( 0, 255, 0 ) );
    convex.setOutlineThickness( 1 );

    sf::RectangleShape rect( sf::Vector2f( 20, 3 ) );
    rect.setOrigin( 10.0, 15.0 );
    rect.setOutlineThickness( 1.0 );
    rect.setOutlineColor( sf::Color( 0, 0, 0, 127 ) );

	for( const Model::Phaser * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );
		radius.setPosition( m->getPosition().x, m->getPosition().y );

		if( !m->isPulseNeeded() )
			circle.setFillColor( sf::Color( 0, 255, 255 ) );
		else
			circle.setFillColor( sf::Color( 0, 64, 64 ) );

        convex.setPoint( 0, sf::Vector2f( m->getMinCorner().x, m->getMinCorner().y ) );
        convex.setPoint( 1, sf::Vector2f( m->getMaxCorner().x, m->getMinCorner().y ) );
        convex.setPoint( 2, sf::Vector2f( m->getMaxCorner().x, m->getMaxCorner().y ) );
        convex.setPoint( 3, sf::Vector2f( m->getMinCorner().x, m->getMaxCorner().y ) );

        if( m->getEnemy() )
        {
            sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f( m->getPosition().x, m->getPosition().y ), m->isPulseNeeded()?sf::Color( 0, 0, 255 ):sf::Color( 255, 0, 0 ) ),
                sf::Vertex(sf::Vector2f( m->getEnemy()->getPosition().x, m->getEnemy()->getPosition().y ), m->isPulseNeeded()?sf::Color( 0, 0, 255 ):sf::Color( 255, 0, 0 ) )
            };
            this->window.draw( line, 2, sf::Lines );
        }

        rect.setPosition( m->getPosition().x, m->getPosition().y );
        rect.setFillColor( sf::Color( 255, 0, 0 ) );
        rect.setSize( sf::Vector2f( m->getPulses() / 5.0 * 20.0, 3 ) );

        this->window.draw( convex );
		this->window.draw( radius );
        this->window.draw( rect );
		this->window.draw( circle );
	}
}
