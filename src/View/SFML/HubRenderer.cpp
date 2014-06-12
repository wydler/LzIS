#include "HubRenderer.hpp"


using namespace View::SFML;


void HubRenderer::draw() const
{
	sf::RectangleShape rect( sf::Vector2f( 20, 20 ) );
	rect.setOrigin( 10.0, 10.0 );
	rect.setOutlineColor( sf::Color::White );
	rect.setOutlineThickness( 2.0f );
	rect.setRotation( 45.0 );

    sf::ConvexShape convex;
    convex.setPointCount(4);
    convex.setOutlineColor( sf::Color( 0, 255, 0 ) );
    convex.setOutlineThickness( 1 );

	for( const Model::Hub * m : this->getModels() )
	{
		rect.setPosition( m->getPosition().x, m->getPosition().y );

		//std::cout << m->getNode()->getOutLinks().size() << std::endl;
		if( m->getConstNode()->getInLinks().size() > 0 )
			rect.setFillColor( sf::Color( 0, 255, 0 ) );
		else
			rect.setFillColor( sf::Color( 0, 0, 0 ) );

        convex.setPoint( 0, sf::Vector2f( m->getMinCorner().x, m->getMinCorner().y ) );
        convex.setPoint( 1, sf::Vector2f( m->getMaxCorner().x, m->getMinCorner().y ) );
        convex.setPoint( 2, sf::Vector2f( m->getMaxCorner().x, m->getMaxCorner().y ) );
        convex.setPoint( 3, sf::Vector2f( m->getMinCorner().x, m->getMaxCorner().y ) );

        this->window.draw( convex );
		this->window.draw( rect );
	}
}
