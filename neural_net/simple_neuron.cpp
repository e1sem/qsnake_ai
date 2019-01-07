#include "simple_neuron.hpp"

#include <cassert>
#include <random>
#include <cmath>

/************************************************************************/

Neuron::Neuron( Layer const& _previous )
	: m_weights( _previous.size(), 0.0 )
{
	assert( !_previous.empty() );

	for( auto && neuron : _previous )
		m_connections.push_back( neuron );
}

/************************************************************************/

double
Neuron::getResult() const noexcept
{
	return calculateResult();
}

/************************************************************************/

void
Neuron::setRandomWeights() noexcept
{
	std::uniform_real_distribution< double > distribution( -1.0, 1.0 );
	std::random_device device;
	std::default_random_engine generator( device() );

	for( auto && weight : m_weights )
		weight = distribution( generator );
}

/************************************************************************/

double
Neuron::activationFunction( double val ) noexcept
{
    return 1.0 / ( 1.0 + std::exp( - val ) );
}

/************************************************************************/

double
Neuron::calculateResult() const noexcept
{
	assert( m_connections.size() == m_weights.size() );

	std::size_t countOfNeurons = m_weights.size();
	double totalSum = 0.0;

	for( std::size_t i = 0; i < countOfNeurons; ++i )
		totalSum += m_connections[i]->getResult()
						* m_weights[i];

	return activationFunction( totalSum );
}

/************************************************************************/
