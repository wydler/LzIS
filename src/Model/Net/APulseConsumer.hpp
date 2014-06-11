#ifndef _MODEL_NET_APULSECONSUMER_INCLUDED_
#define _MODEL_NET_APULSECONSUMER_INCLUDED_


#include "APulseNodeActor.hpp"


namespace Model
{
	namespace Net
	{
		class PulseNode;
		class APulseConsumer : public virtual APulseNodeActor
		{
		public:
			virtual bool isPulseNeeded() const = 0;
			virtual bool givePulse() = 0;
			virtual int getPriority() const = 0;
		};
	}
}


#endif
