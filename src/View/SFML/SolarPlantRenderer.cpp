#include "SolarPlantRenderer.hpp"

#include "AssetManager.hpp"

using namespace View::SFML;


void SolarPlantRenderer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
    sf::CircleShape circle( 16, 6 );
    circle.setOrigin( 16, 16 );
	circle.setOutlineColor( sf::Color::White );
    circle.setOutlineThickness( 0 );

	sf::Text text;
	text.setFont(*View::SFML::AssetManager::getFont( "visitor1.ttf" ));
	text.setColor( sf::Color( 255, 0, 0 ) );
	text.setCharacterSize(20);

	for( const Model::SolarPlant * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );

		if( m->isPulseAvailable() )
            circle.setFillColor( sf::Color( 255, 255, 0 ) );
		else
            circle.setFillColor( sf::Color( 160, 160, 0 ) );

		text.setString( std::to_string( m->getPulses() ) );
		text.setPosition( m->getPosition().x, m->getPosition().y );
		text.setOrigin( text.getLocalBounds().width/2-1, -text.getLocalBounds().height );

        target.draw( circle, states );
        target.draw( text, states );
	}
}
