#include "HubRenderer.hpp"


using namespace View::SFML;


void HubRenderer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
    sf::CircleShape rect( 12 );
    rect.setOrigin( 12, 12 );
    rect.setOutlineColor( sf::Color( 0, 200, 200 ) );
    rect.setOutlineThickness( 2.0f );

	for( const Model::Hub * m : this->getModels() )
	{
		rect.setPosition( m->getPosition().x, m->getPosition().y );

		if( m->getConstNode()->getInLinks().size() > 0 )
            rect.setFillColor( sf::Color( 0, 200, 200 ) );
        else
            rect.setFillColor( sf::Color( 0, 100, 100 ) );

        target.draw( rect, states );
	}
}
