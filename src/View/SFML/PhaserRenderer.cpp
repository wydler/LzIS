#include "PhaserRenderer.hpp"


using namespace View::SFML;


void PhaserRenderer::draw() const
{
	sf::CircleShape circle( 10.0f );
	circle.setOrigin( 10.0f, 10.0f );
	circle.setOutlineColor( sf::Color::White );
	circle.setOutlineThickness( 2.0f );

	sf::CircleShape radius( 50.0f );
	radius.setOrigin( 50.0f, 50.0f );
	radius.setOutlineColor( sf::Color( 255, 0, 0, 100 ) );
	radius.setOutlineThickness( 1.0f );
	radius.setFillColor( sf::Color( 0, 255, 0, 0 ) );

	for( const Model::Phaser * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );
		radius.setPosition( m->getPosition().x, m->getPosition().y );

		if( !m->isPulseNeeded() )
			circle.setFillColor( sf::Color( 0, 255, 255 ) );
		else
			circle.setFillColor( sf::Color( 0, 64, 64 ) );

		this->window.draw( radius );
		this->window.draw( circle );
	}
}
