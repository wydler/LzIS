#include <iostream>
#include <typeinfo>
#include <set>

#include <math.h>

#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include <SFML/Graphics.hpp>

#include "Model/Updater.hpp"
#include "Model/IntervalStepUpdater.hpp"
#include "Model/Station/SolarPlant.hpp"
#include "Model/Station/Phaser.hpp"
#include "Model/Station/Hub.hpp"
#include "Model/Unit/Tank.hpp"
#include "Model/Net/PulseDistributor.hpp"
#include "Model/Net/PulseNode.hpp"
#include "Model/AField2D.hpp"
#include "Model/Field/Grass.hpp"
#include "View/SFML/SceneManager.hpp"
#include "View/SFML/AssetManager.hpp"


enum MouseMode
{
	SOLARPLANT,
	PHASER,
	HUB,
	TANK,
	LINK,
	UNLINK
};

static const int SIZE_X = 600;
static const int SIZE_Y = 600;
static const int FIELDS_X = 16;
static const int FIELDS_Y = 16;

MouseMode mouseMode = SOLARPLANT;

Model::Updater * updater;
Model::IntervalStepUpdater * intervalStepUpdater;
Model::Net::PulseDistributor * pulseDistributor;

View::SFML::SceneManager * sceneManager;

static Model::AField2D * currentField = nullptr;
static Model::APositionable2D * draggedObject = nullptr;
static Model::Net::APulseNodeActor * linkSource = nullptr;
static Model::Net::APulseNodeActor * linkSink = nullptr;

template< typename T >
static T * getAt( const glm::vec2 & pos )
{
    for( auto i : sceneManager->getSolarPlants() )
	{
		if( pos.x > i->getMinCorner().x
		 && pos.x < i->getMaxCorner().x
		 && pos.y > i->getMinCorner().y
		 && pos.y < i->getMaxCorner().y
		)
			return i;
	}
    for( auto i : sceneManager->getPhasers() )
	{
		if( pos.x > i->getMinCorner().x
		 && pos.x < i->getMaxCorner().x
		 && pos.y > i->getMinCorner().y
		 && pos.y < i->getMaxCorner().y
		)
			return i;
	}
    for( auto i : sceneManager->getHubs() )
	{
		if( pos.x > i->getMinCorner().x
		 && pos.x < i->getMaxCorner().x
		 && pos.y > i->getMinCorner().y
		 && pos.y < i->getMaxCorner().y
		)
			return i;
	}

	return nullptr;
}


static void click( const glm::vec2 & pos )
{
    if( !currentField )
        return;
	Model::ABoundingBox2D * obj = getAt<Model::ABoundingBox2D>( pos );
	if( obj )
	{
		if( typeid( *obj ) == typeid( Model::SolarPlant ) )
			static_cast< Model::SolarPlant * >( obj )->setPulses( 10 );
		else if( typeid( *obj ) == typeid( Model::Phaser ) )
			static_cast< Model::Phaser * >( obj )->setPulses( 0 );
		return;
	}
	switch( mouseMode )
	{
	case SOLARPLANT:
	{
		Model::SolarPlant * m = new Model::SolarPlant;
        m->setPosition( currentField->getPosition() );
        sceneManager->getSolarPlants().insert( m );
		updater->addUpdateable( m );
        sceneManager->getSolarPlantRenderer()->addModel( m );
		pulseDistributor->addProvider( m );
		break;
	}
	case PHASER:
	{
		Model::Phaser * m = new Model::Phaser;
        m->setPosition( currentField->getPosition() );
        sceneManager->getPhasers().insert( m );
		updater->addUpdateable( m );
        intervalStepUpdater->addStepUpdateable( m );
        sceneManager->getPhaserRenderer()->addModel( m );
		pulseDistributor->addConsumer( m );
		break;
	}
	case HUB:
	{
		Model::Hub * m = new Model::Hub;
        m->setPosition( currentField->getPosition() );
        sceneManager->getHubs().insert( m );
		updater->addUpdateable( m );
        sceneManager->getHubRenderer()->addModel( m );
		pulseDistributor->addProvider( m );
		pulseDistributor->addConsumer( m );
		break;
	}
	case TANK:
	{
		Model::Tank * m = new Model::Tank;
        m->setPosition( currentField->getPosition() );
		updater->addUpdateable( m );
        sceneManager->getEnemies().insert( m );
        sceneManager->getEnemyRenderer()->addModel( m );
		break;
	}
	default:
		break;
	}
}


static void dragStart( const glm::vec2 & from )
{
	switch( mouseMode )
	{
		case SOLARPLANT:
		case PHASER:
		case HUB:
		case TANK:
			if( !draggedObject )
				draggedObject = getAt<Model::APositionable2D>( from );
			break;
		case LINK:
		case UNLINK:
			linkSource = getAt<Model::Net::APulseNodeActor>( from );
			break;
	}
}


static void drag( const glm::vec2 & to )
{
	switch( mouseMode )
	{
		case SOLARPLANT:
		case PHASER:
		case HUB:
			if( draggedObject )
			{
				draggedObject->setPosition( to );
			}
			break;
		default:
			break;
	}
}


static void dragStop( const glm::vec2 & to )
{
	switch( mouseMode )
	{
		case SOLARPLANT:
		case PHASER:
		case HUB:
		case TANK:
			if( draggedObject )
			{
				draggedObject->setPosition( to );
				draggedObject = nullptr;
			}
			break;
		case LINK:
			{
				linkSink = getAt<Model::Net::APulseNodeActor>( to );
				if( !linkSource || !linkSink )
					return;
				Model::Net::PulseLink * link = new Model::Net::PulseLink;
				if( Model::Net::PulseNode::setLink( linkSource->getNode(), linkSink->getNode(), link ) )
				{
                    sceneManager->getPulseLinkRenderer()->addModel( link );
                    sceneManager->getLinks().insert( link );
				}
			}
			break;
		case UNLINK:
			{
				linkSink = getAt<Model::Net::APulseNodeActor>( to );
				if( !linkSource || !linkSink )
					return;
				Model::Net::PulseLink * link = const_cast< Model::Net::PulseLink * >( linkSource->getNode()->getOutLink( linkSink->getNode() ) );
				if( link )
				{
					if( Model::Net::PulseNode::setLink( linkSource->getNode(), linkSink->getNode(), nullptr ) )
					{
                        sceneManager->getPulseLinkRenderer()->removeModel( link );
                        sceneManager->getLinks().erase( link );
					}
				}
			}
			break;
	}
}


int main( int argc, char ** argv )
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window( sf::VideoMode( SIZE_X, SIZE_Y ), "LzIS", sf::Style::Default, settings );
	window.setVerticalSyncEnabled(true);

    sf::View gui;
    gui.setSize( SIZE_X, SIZE_Y );
    gui.setCenter( SIZE_X/2, SIZE_Y/2 );

    sf::View world;
    world.setSize( SIZE_X, SIZE_Y );
    world.setCenter( SIZE_X/2, SIZE_Y/2 );

	pulseDistributor = new Model::Net::PulseDistributor;

	intervalStepUpdater = new Model::IntervalStepUpdater;
    intervalStepUpdater->setInterval( 0.2 );
	intervalStepUpdater->addStepUpdateable( pulseDistributor );

	updater = new Model::Updater;
	updater->addUpdateable( intervalStepUpdater );

    sceneManager = View::SFML::SceneManager::instance();

    for( int i=0; i<16; i++ )
    {
        for( int j=0; j<16; j++ )
        {
            int offset = 0;
            if( i%2 == 0)
                offset = 20;
            Model::Field::Grass * hex = new Model::Field::Grass();
            hex->setPosition( glm::vec2( j*40+offset, i*34 ) );
            sceneManager->getFields().insert( hex );
            sceneManager->getFieldRenderer()->addModel( hex );
        }
    }

	sf::Clock clock;
	while( window.isOpen() )
	{
		sf::Time elapsed = clock.restart();

		updater->update( elapsed.asSeconds() );

		window.clear( sf::Color::Black );

		sf::Event event;
		while( window.pollEvent(event) )
		{
			if( event.type == sf::Event::Closed )
				window.close();
			static glm::vec2 lastMousePos = glm::vec2(0,0);
			static bool dragging = false;
			switch( event.type )
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch( event.key.code )
					{
					case sf::Keyboard::Num1:
						mouseMode = SOLARPLANT;
						break;
					case sf::Keyboard::Num2:
						mouseMode = PHASER;
						break;
					case sf::Keyboard::Num3:
						mouseMode = HUB;
						break;
					case sf::Keyboard::Num4:
						mouseMode = LINK;
						break;
					case sf::Keyboard::Num5:
						mouseMode = UNLINK;
						break;
					case sf::Keyboard::Num9:
						mouseMode = TANK;
						break;
                    case sf::Keyboard::Left:
                        world.move( -10,   0 );
                        break;
                    case sf::Keyboard::Up:
                        world.move(   0, -10 );
                        break;
                    case sf::Keyboard::Right:
                        world.move(  10,   0 );
                        break;
                    case sf::Keyboard::Down:
                        world.move(   0,  10 );
                        break;
					default:
						break;
					}
				case sf::Event::MouseButtonPressed:
					switch( event.mouseButton.button )
					{
					case sf::Mouse::Left:
                    {
                        sf::Vector2f pos = window.mapPixelToCoords( sf::Vector2i( event.mouseButton.x, event.mouseButton.y ), world );
                        lastMousePos = glm::vec2( pos.x, pos.y );
						break;
                    }
                    case sf::Mouse::Right:
                    {
                        sf::Vector2f pos = window.mapPixelToCoords( sf::Vector2i( event.mouseButton.x, event.mouseButton.y ), world );
                        std::cout << pos.x << " | " << pos.y << std::endl;
                    }
					default:
						break;
					}
					break;
				case sf::Event::MouseMoved:
					{
                        sf::Vector2f pos = window.mapPixelToCoords( sf::Vector2i( event.mouseMove.x, event.mouseMove.y ), world );

                        Model::AField2D * field = sceneManager->getFieldAt( glm::vec2( pos.x, pos.y ) );
                        if( field )
                        {
                            for( auto i: sceneManager->getNextFieldsTo( field, 1 ) )
                            {
                                i->setState( FieldState::ACTIVE );
                            }
                        }
                        if( currentField )
                            currentField->setState( FieldState::IDLE );
                        if( field )
                            field->setState( FieldState::HOVER );

                        currentField = field;

						if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
						{
                            glm::vec2 currentMousePos( pos.x, pos.y );
							if( !dragging )
							{
								if( glm::distance( currentMousePos, lastMousePos ) >= 5.0f )
								{
									dragStart( currentMousePos );
									dragging = true;
								}
							}
							else
								drag( currentMousePos );
						}
					}
					break;
				case sf::Event::MouseButtonReleased:
					switch( event.mouseButton.button )
					{
					case sf::Mouse::Left:
						{
                            sf::Vector2f pos = window.mapPixelToCoords( sf::Vector2i( event.mouseButton.x, event.mouseButton.y ), world );
                            glm::vec2 currentMousePos( pos.x, pos.y );
							if( dragging )
							{
								dragStop( currentMousePos );
								dragging = false;
							}
							else
							{
								click( currentMousePos );
							}
						}
						break;
					default:
						break;
					}
					break;
                case sf::Event::MouseWheelMoved:
                {
                    if( event.mouseWheel.delta < 0 )
                    {
                        world.zoom( 1.05 );
                    }
                    else if( event.mouseWheel.delta > 0 )
                    {
                        world.zoom( 0.95 );
                    }
                    break;
                }
				default:
					break;
			}
		}

        window.setView( world );

        window.draw( *sceneManager );


        window.setView( gui );

        // TODO draw gui

		window.display();
	}
}
