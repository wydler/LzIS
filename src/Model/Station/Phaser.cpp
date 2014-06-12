#include "Phaser.hpp"

#include <float.h>

#include "../Net/PulseNode.hpp"
#include "../../View/SFML/SceneManager.hpp"


using namespace Model;


Phaser::Phaser()
{
	this->node = new Net::PulseNode;
	node->setInLinkCapacity( 4 );
	node->setOutLinkCapacity( 4 );
}


Phaser::~Phaser()
{
	delete this->node;
}


void Phaser::update( double delta )
{

}

void Phaser::step()
{
    this->target = View::SFML::SceneManager::instance()->getNextEnemy( this->getPosition(), 100.0 );

    if( this->getPulses() > 0 && this->target )
    {
        this->pulses--;
        this->target->hit( 10.0 );
        std::cout << this << ": hit target " << this->target << std::endl;
    }
}
