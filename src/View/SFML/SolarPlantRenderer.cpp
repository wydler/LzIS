#include "SolarPlantRenderer.hpp"

#include "AssetManager.hpp"

using namespace View::SFML;


void SolarPlantRenderer::draw() const
{
	sf::CircleShape circle( 10.0f );
	circle.setOrigin( 10.0f, 10.0f );
	circle.setOutlineColor( sf::Color::White );
	circle.setOutlineThickness( 2.0f );

	sf::Text text;
	text.setFont(*View::SFML::AssetManager::getFont( "visitor1.ttf" ));
	text.setColor( sf::Color( 255, 0, 0 ) );
	text.setCharacterSize(20);

    sf::ConvexShape convex;
    convex.setPointCount(4);
    convex.setOutlineColor( sf::Color( 0, 255, 0 ) );
    convex.setOutlineThickness( 1 );

	for( const Model::SolarPlant * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );

		if( m->isPulseAvailable() )
			circle.setFillColor( sf::Color( 255, 255, 0 ) );
		else
			circle.setFillColor( sf::Color( 64, 64, 0 ) );

		text.setString( std::to_string( m->getPulses() ) );
		text.setPosition( m->getPosition().x, m->getPosition().y );
		text.setOrigin( text.getLocalBounds().width/2-1, -text.getLocalBounds().height );

        convex.setPoint( 0, sf::Vector2f( m->getMinCorner().x, m->getMinCorner().y ) );
        convex.setPoint( 1, sf::Vector2f( m->getMaxCorner().x, m->getMinCorner().y ) );
        convex.setPoint( 2, sf::Vector2f( m->getMaxCorner().x, m->getMaxCorner().y ) );
        convex.setPoint( 3, sf::Vector2f( m->getMinCorner().x, m->getMaxCorner().y ) );

        this->window.draw( convex );
		this->window.draw( circle );
		this->window.draw( text );
	}
}
