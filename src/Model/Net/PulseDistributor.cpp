#include "PulseDistributor.hpp"

#include "APulseConsumer.hpp"
#include "APulseProvider.hpp"
#include "PulseNode.hpp"
#include "PulseLink.hpp"

#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_set>

#include <assert.h>


using namespace Model::Net;


template< typename T >
class AIterativeDeepeningSearch
{
public:
	virtual bool isGoal( const T * node ) const = 0;

	virtual std::vector< const T * > getSuccessors( const T * node ) const = 0;

	std::vector< std::vector< const T * > > depthLimitedSearch( const T * from, unsigned int maxDepth, unsigned int currentDepth = 0 )
	{
		std::vector< std::vector< const T * > > foundGoals;
		std::vector< const T * > successors = this->getSuccessors( from );
		for( auto & successor : successors )
		{
			if( this->isGoal( successor ) )
				foundGoals.push_back( std::vector< const T * >( {successor,from} ) );
		}
		if( currentDepth >= maxDepth )
			return foundGoals;
		for( auto & successor : successors )
		{
			std::vector< std::vector< const T * > > newGoals = this->depthLimitedSearch( successor, maxDepth, currentDepth + 1 );
			if( newGoals.size() )
			{
				for( auto & goal : newGoals )
					goal.push_back( from );
				foundGoals.insert( foundGoals.end(), newGoals.begin(), newGoals.end() );
			}
		}
		return foundGoals;
	}

	std::vector< std::vector< const T * > > findShortestPaths( const T * from, unsigned int maxDepth )
	{
		std::vector< std::vector< const T * > > paths;
		for( unsigned int depth = 0; depth < maxDepth; depth++ )
		{
			paths = depthLimitedSearch( from, depth );
			if( paths.size() != 0 )
				break;
		}
		return paths;
	}
};


class PulseNodePathSearch : public AIterativeDeepeningSearch< PulseLink >
{
public:
	virtual bool isGoal( const PulseLink * link ) const override
		{ return goals.count( link->from ); }

	virtual std::vector< const PulseLink * > getSuccessors( const PulseLink * link ) const override
	{
		std::vector< const PulseLink * > successors;
		const PulseNode * nextNode = link->from;
		if( !nextNode )
			return successors;
		for( const auto & linkEntry : nextNode->getInLinks() )
		{
			PulseLink * link = linkEntry.second;
			if( link->pulse )
				continue; // cannot use link that carries pulse
			successors.push_back( link );
		}
		return successors;
	}

	void setGoals( const std::unordered_set< const PulseNode * > & goals )
		{ this->goals = goals; }

	bool addGoal( const PulseNode * node )
		{ return goals.insert( node ).second; }

	bool removeGoal( const PulseNode * node )
		{ return goals.erase( node ); }

private:
	std::unordered_set< const PulseNode * > goals;
};


void PulseDistributor::step()
{
	for( PulseNode * node : this->nodes )
	{
		node->step();
	}

	PulseNodePathSearch pulseNodePathSearch;

	// generate a map for all available providers to quickly find the matching provider for a given node
	std::map< const PulseNode *, APulseProvider * > availableProvidersMap;
	for( APulseProvider * provider : this->providers )
	{
		if( !provider->isPulseAvailable() )
			continue;
		availableProvidersMap[ provider->getNode() ] = provider;
		pulseNodePathSearch.addGoal( provider->getNode() );
	}
	if( availableProvidersMap.empty() )
		return; // no providers that could pulse

	// randomize which consumer gets served first
	std::random_shuffle( consumers.begin(), consumers.end() );

	for( APulseConsumer * consumer : this->consumers )
	{
		while( consumer->isPulseNeeded() && !availableProvidersMap.empty() )
		{
			std::cerr << "Searchin shortest paths for " << consumer->getNode() << "\n";
			// search for all shortest paths to a provider
			std::vector< std::vector< const PulseLink * > > paths;
			PulseLink dummyLink;
			dummyLink.from = consumer->getNode();
			paths = pulseNodePathSearch.findShortestPaths( &dummyLink, 8 );
			if( paths.empty() )
				break; // none found - continue with next consumer
			std::cerr << "found " << paths.size() << " paths:\n";
			for( unsigned int i = 0; i<paths.size(); i++ )
			{
				std::cerr << "\t" << "path " << i << ":\n";
				for( const PulseLink * l : paths[i] )
					std::cerr << "\t\t" << l << "\n";
			}

			// pick a random path to the provider's node
			std::vector< const PulseLink * > path = paths[ rand() % paths.size() ];
			assert( !path.empty() ); // empty path - should never happen

			// retrieve provider for this node
			auto providerIt = availableProvidersMap.find( path[0]->from );
			assert( providerIt != availableProvidersMap.end() ); // got a node not in the list of available providers - should never happen
			APulseProvider * provider = providerIt->second;

			// pulse all links to this node
			for( const PulseLink * link : path )
			{
				const_cast< PulseLink * >(link)->pulse = true;
			}

			// transfer pulse
			consumer->givePulse();
			provider->takePulse();

			// remove provider if no more pulses left
			if( !provider->isPulseAvailable() )
			{
				pulseNodePathSearch.removeGoal( provider->getNode() );
				availableProvidersMap.erase( provider->getNode() );
			}
		}
	}
}


bool PulseDistributor::addNode( PulseNode * node )
{
	auto it = std::find( this->nodes.begin(), this->nodes.end(), node );
	if( it != this->nodes.end() )
		return false; // already added

	this->nodes.push_back( node );
	return true;
}


bool PulseDistributor::addConsumer( APulseConsumer * consumer )
{
	auto it = std::find( this->consumers.begin(), this->consumers.end(), consumer );
	if( it != this->consumers.end() )
		return false; // already added

	this->consumers.push_back( consumer );
	this->addNode( consumer->getNode() );
	return true;
}


bool PulseDistributor::addProvider( APulseProvider * provider )
{
	auto it = std::find( this->providers.begin(), this->providers.end(), provider );
	if( it != this->providers.end() )
		return false; // already added

	this->providers.push_back( provider );
	this->addNode( provider->getNode() );
	return true;
}


bool PulseDistributor::removeNode( PulseNode * node )
{
	auto it = std::find( this->nodes.begin(), this->nodes.end(), node );
	if( it == this->nodes.end() )
		return false; // not in list

	this->nodes.erase( it );
	return true;
}


bool PulseDistributor::removeConsumer( APulseConsumer * consumer )
{
	auto it = std::find( this->consumers.begin(), this->consumers.end(), consumer );
	if( it == this->consumers.end() )
		return false; // not in list

	this->consumers.erase( it );
	this->removeNode( consumer->getNode() );
	return true;
}


bool PulseDistributor::removeProvider( APulseProvider * provider )
{
	auto it = std::find( this->providers.begin(), this->providers.end(), provider );
	if( it == this->providers.end() )
		return false; // not in list

	this->providers.erase( it );
	this->removeNode( provider->getNode() );
	return true;
}
