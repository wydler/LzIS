#ifndef _MODEL_NET_APULSENODEACTOR_INCLUDED_
#define _MODEL_NET_APULSENODEACTOR_INCLUDED_


namespace Model
{
	namespace Net
	{
		class PulseNode;
		class APulseNodeActor
		{
		public:
			virtual PulseNode * getNode() = 0;
			const PulseNode * getConstNode() const
				{ return const_cast<APulseNodeActor*>(this)->getNode(); }
		};
	}
}


#endif
