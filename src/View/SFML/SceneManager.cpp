#include "SceneManager.hpp"

#include <iostream>

#include <float.h>

#include <glm/geometric.hpp>


using namespace View::SFML;


SceneManager * SceneManager::_instance = 0;


SceneManager::SceneManager()
{
    enemyRenderer = new View::SFML::EnemyRenderer();
    solarPlantRenderer = new View::SFML::SolarPlantRenderer();
    phaserRenderer = new View::SFML::PhaserRenderer();
    hubRenderer = new View::SFML::HubRenderer();
    pulseLinkRenderer = new View::SFML::PulseLinkRenderer();
    fieldRenderer = new View::SFML::FieldRenderer();
}


void SceneManager::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
    target.draw( *fieldRenderer, states );
    //fieldRenderer->draw();
    target.draw( *pulseLinkRenderer, states );
    //pulseLinkRenderer->draw();
    target.draw( *hubRenderer, states );
    //hubRenderer->draw();
    target.draw( *solarPlantRenderer, states );
    //solarPlantRenderer->draw();
    target.draw( *phaserRenderer, states );
    //phaserRenderer->draw();
    target.draw( *enemyRenderer, states );
    //sceneManager->getTankRenderer()->draw();
}


Model::ADestroyable * SceneManager::getNextEnemy( glm::vec2 pos, double maxDistance )
{
    double distance = DBL_MAX;
    Model::ADestroyable * target = nullptr;
    for( Model::ADestroyable * m : enemies )
    {
        if( m->getState() == LifeState::ALIVE )
        {
            double dist = glm::distance( pos, m->getPosition() );
            if( dist < maxDistance && dist < distance )
            {
                distance = dist;
                target = m;
            }
        }
    }

    return target;
}


Model::AField2D * SceneManager::getFieldAt( const glm::vec2 & pos )
{
    for( auto i : fields )
    {
        if( i->contains( glm::vec2( pos.x, pos.y ) ) )
            return i;
    }

    return nullptr;
}


std::set< Model::AField2D * > & SceneManager::getNextFieldsTo( Model::AField2D * field, const int level )
{
    std::set< Model::AField2D * > next;

    for( auto i : fields )
    {
        if( i->contains( glm::vec2( field->getPosition().x-40, field->getPosition().y    ) ) ||
            i->contains( glm::vec2( field->getPosition().x+40, field->getPosition().y    ) ) ||
            i->contains( glm::vec2( field->getPosition().x-20, field->getPosition().y-34 ) ) ||
            i->contains( glm::vec2( field->getPosition().x+20, field->getPosition().y-34 ) ) ||
            i->contains( glm::vec2( field->getPosition().x-20, field->getPosition().y+34 ) ) ||
            i->contains( glm::vec2( field->getPosition().x+20, field->getPosition().y+34 ) )
            )
            next.insert( i );
    }

    return next;
}
