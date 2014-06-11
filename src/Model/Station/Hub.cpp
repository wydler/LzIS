#include "Hub.hpp"

#include "../Net/PulseNode.hpp"


using namespace Model;


Hub::Hub()
{
	this->node = new Net::PulseNode;
	node->setInLinkCapacity( 5 );
	node->setOutLinkCapacity( 5 );
}


Hub::~Hub()
{
	delete this->node;
}


void Hub::update( double delta )
{

}