#include "HubRenderer.hpp"


using namespace View::SFML;


void HubRenderer::draw() const
{
	sf::RectangleShape rect( sf::Vector2f( 20, 20 ) );
	rect.setOrigin( 10.0, 10.0 );
	rect.setOutlineColor( sf::Color::White );
	rect.setOutlineThickness( 2.0f );
	rect.setRotation( 45.0 );

	for( const Model::Hub * m : this->getModels() )
	{
		rect.setPosition( m->getPosition().x, m->getPosition().y );

		//std::cout << m->getNode()->getOutLinks().size() << std::endl;
		if( m->isPulseAvailable() )
			rect.setFillColor( sf::Color( 0, 255, 0 ) );
		else
			rect.setFillColor( sf::Color( 0, 0, 0 ) );

		this->window.draw( rect );
	}
}
