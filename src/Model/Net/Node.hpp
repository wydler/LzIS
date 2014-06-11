#ifndef _MODEL_NET_NODE_INCLUDED_
#define _MODEL_NET_NODE_INCLUDED_


#include <map>


namespace Model
{
	namespace Net
	{
		template< typename TNode, typename TLink >
		class Node
		{
		public:
			static bool setLink( TNode * source, TNode * other, TLink * link )
			{
				bool isLinked = source->getOutLink( other );
				if( link ) // if linking
				{
					if( isLinked )
						return false;
				}
				else
				{
					if( !isLinked )
						return false;
				}
				source->setOutLink( other, link );
				other->setInLink( source, link );
				return true;
			}

			const std::map< const TNode *, TLink * > & getOutLinks() const
			{
				return this->outLinks;
			}

			const std::map< const TNode *, TLink * > & getInLinks() const
			{
				return this->inLinks;
			}

			const TLink * getOutLink( const TNode * other ) const
			{
				auto it = this->outLinks.find( other );
				if( it == outLinks.end() )
					return nullptr; // not linked to this node
				return (*it).second;
			}

			const TLink * getInLink( const TNode * other ) const
			{
				auto it = this->inLinks.find( other );
				if( it == inLinks.end() )
					return nullptr; // not linked to this node
				return (*it).second;
			}

		private:
			std::map< const TNode *, TLink * > outLinks;
			std::map< const TNode *, TLink * > inLinks;

			virtual void setOutLink( const TNode * other, TLink * link )
			{
				if( link == nullptr )
					this->outLinks.erase( other );
				else
					this->outLinks[ other ] = link;
			}

			virtual void setInLink( const TNode * other, TLink * link )
			{
				if( link == nullptr )
					this->inLinks.erase( other );
				else
					this->inLinks[ other ] = link;
			}
		};
	}
}


#endif
