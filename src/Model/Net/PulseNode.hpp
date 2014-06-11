#ifndef _MODEL_NET_PULSENODE_INCLUDED_
#define _MODEL_NET_PULSENODE_INCLUDED_


#include "Node.hpp"
#include "PulseLink.hpp"
#include "../AStepUpdateable.hpp"

#include <glm/vec2.hpp>

#include <iostream>
#include <set>


namespace Model
{
	namespace Net
	{
		class PulseNode : public Node< PulseNode, PulseLink >, public AStepUpdateable
		{
		public:
			static bool setLink( PulseNode * source, PulseNode * other, PulseLink * link )
			{
				if( link ) // if linking
				{
					if( source->getOutLinks().size() >= source->getOutLinkCapacity() )
						return false; // abort if source can't take any more outgoing links
					if( other->getInLinks().size() >= other->getInLinkCapacity() )
						return false; // abort if other node can't take any more incoming links
					link->from = source;
					link->to = other;
				}
				return Node< PulseNode, PulseLink >::setLink( source, other, link );
			}

			PulseNode() {}
			virtual ~PulseNode() {}

			const glm::vec2 & getPosition() const { return this->position; }
			void setPosition( const glm::vec2 & position ) { this->position = position; }

			float getRadius() const { return this->radius; }
			void setRadius( float radius ) { this->radius = radius; }

			unsigned int getOutLinkCapacity() const { return this->outLinkCapacity; }
			void setOutLinkCapacity( unsigned int outLinkCapacity ) { this->outLinkCapacity = outLinkCapacity; }

			unsigned int getInLinkCapacity() const { return this->inLinkCapacity; }
			void setInLinkCapacity( unsigned int inLinkCapacity ) { this->inLinkCapacity = inLinkCapacity; }

			virtual void step() override
			{
				for( auto & linkEntry : this->getOutLinks() )
				{
					PulseLink * link = linkEntry.second;
					link->pulse = false;
				}
			}

		private:
			glm::vec2 position;
			float radius = 1.0f;
			unsigned int outLinkCapacity = 4;
			unsigned int inLinkCapacity = 4;
		};
	}
}


#endif
