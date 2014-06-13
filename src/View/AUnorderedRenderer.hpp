#ifndef _VIEW_AUNORDEREDRENDERER_INCLUDED_
#define _VIEW_AUNORDEREDRENDERER_INCLUDED_


#include "ADrawable.hpp"

#include <set>


namespace View
{
	template< typename T >
    class AUnorderedRenderer
	{
	public:

		bool addModel( const T * model )
			{ return models.insert( model ).second; }

		bool removeModel( const T * model )
			{ return models.erase( model ) != 0; }

		const std::set< const T * > & getModels() const
			{ return models; }

	private:
		std::set< const T * > models;
	};
}


#endif
