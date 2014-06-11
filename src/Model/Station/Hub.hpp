#ifndef _MODEL_HUB_INCLUDED_
#define _MODEL_HUB_INCLUDED_


#include "../APositionable2D.hpp"
#include "../ABoundingBox2D.hpp"
#include "../AUpdateable.hpp"
#include "../Net/APulseConsumer.hpp"
#include "../Net/APulseProvider.hpp"
#include "../Net/PulseNode.hpp"


namespace Model
{
	class Hub : public AUpdateable, public Net::APulseProvider, public Net::APulseConsumer, public APositionable2D, public ABoundingBox2D
	{
	public:
		Hub();
		virtual ~Hub();

		virtual void update( double delta ) override;

		virtual Net::PulseNode * getNode() override { return this->node; }
		virtual bool isPulseNeeded() const override { return this->pulses == 0; }
		virtual bool givePulse() { this->pulses++; return true; }
		virtual int getPriority() const override { return 0; }
		virtual bool isPulseAvailable() const override { return this->pulses; }
		virtual bool takePulse() override
		{
			if( !pulses )
				return false;
			pulses--;
			return true;
		}
		virtual glm::vec2 getPosition() const { return this->position; }
		virtual void setPosition( const glm::vec2 & position ) { this->position = position; this->node->setPosition( position ); }
		virtual glm::vec2 getMaxCorner() const { return this->position + glm::vec2( 30, 30 ); }
		virtual glm::vec2 getMinCorner() const { return this->position - glm::vec2( 30, 30 ); }

		void setPulses( unsigned int pulses ) { this->pulses = pulses; }
		unsigned int getPulses() const { return this->pulses; }
	private:
		Net::PulseNode * node = nullptr;
		unsigned int pulses = 0;
		glm::vec2 position = glm::vec2(0,0);
	};
}


#endif
