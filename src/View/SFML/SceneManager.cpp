#include "SceneManager.hpp"

#include <iostream>

#include <float.h>

#include <glm/geometric.hpp>


using namespace View::SFML;


SceneManager * SceneManager::_instance = 0;


SceneManager::SceneManager()
{
    std::cout << "new instance" << std::endl;
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
