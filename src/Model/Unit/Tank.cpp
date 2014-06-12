#include "Tank.hpp"

#include "../../View/SFML/SceneManager.hpp"


using namespace Model;


Tank::Tank()
{
}


Tank::~Tank()
{
}


void Tank::update( double delta )
{
}


void Tank::hit( const double damage )
{
    this->life -= damage;

    if( this->life <= 0 )
    {
        View::SFML::SceneManager::instance()->getEnemies()->erase( this );
        View::SFML::SceneManager::instance()->getTankRenderer()->removeModel( this );
        this->state = LifeState::DEAD;
    }
}
