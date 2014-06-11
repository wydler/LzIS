#include "PulseLinkRenderer.hpp"
#include "../../Model/Net/PulseNode.hpp"
#include <glm/geometric.hpp>


using namespace View::SFML;


void PulseLinkRenderer::draw() const
{
	sf::Texture tex;
	tex.loadFromFile( "../assets/images/link.png" );
	sf::CircleShape shape( 4 );
	shape.setOrigin( 4, 4 );
	shape.setFillColor( sf::Color( 255, 255, 0, 200 ) );
	shape.setOutlineColor( sf::Color( 255, 255, 0, 200 ) );

	for( const Model::Net::PulseLink * m : this->getModels() )
	{
		if( !m->from || !m->to )
			continue;
		glm::vec2 from = m->from->getPosition();
		glm::vec2 to = m->to->getPosition();

		sf::Vertex line[2] =
		{
			sf::Vertex(sf::Vector2f( from.x, from.y ), m->pulse?sf::Color( 128, 0, 255 ):sf::Color( 128, 0, 255, 64 ) ),
			sf::Vertex(sf::Vector2f( to.x, to.y ), m->pulse?sf::Color( 64, 0, 255 ):sf::Color( 64, 0, 255, 64 ) )
		};
		this->window.draw( line, 2, sf::Lines );

		glm::vec2 diff = to - from;

		shape.setPosition( ( from.x+to.x ) / 2, ( from.y+to.y ) / 2 );
		if( m->pulse ) {
			shape.setOutlineThickness( 1.0 );
		} else {
			shape.setOutlineThickness( 0.0 );
		}
		double x = atan2( diff.y, diff.x );
		x = (x > 0 ? x : (2*M_PI + x)) * 360 / (2*M_PI);
		shape.setRotation( x+45 );
		//shape.setTexture( &tex );
		this->window.draw( shape );
	}
}
