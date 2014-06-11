#ifndef _MODEL_NET_APULSEPROVIDER_INCLUDED_
#define _MODEL_NET_APULSEPROVIDER_INCLUDED_


#include "APulseNodeActor.hpp"


namespace Model
{
	namespace Net
	{
		class PulseNode;
		class APulseProvider : public virtual APulseNodeActor
		{
		public:
			virtual bool isPulseAvailable() const = 0;
			virtual bool takePulse() = 0;
		};
	}
}


#endif
