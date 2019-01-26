#include "simple_neuron.hpp"
#include "receptive_neuron.hpp"

#include <cstdlib>
#include <cassert>
#include <cmath>

/************************************************************************/

template< typename T >
Neuron::Neuron( T const& previous )
    :	m_weights( previous.size(), 0.0 )
{
    assert( !previous.empty() );

    for( auto && neuron : previous )
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
	for( auto && weight : m_weights )
        weight = ( std::rand() % 201 - 100 ) / 100.0;
}

/************************************************************************/

int
Neuron::getLinksCount() const noexcept
{
	return m_connections.size();
}

/************************************************************************/

std::vector< double > const&
Neuron::getWeights() const noexcept
{
    return m_weights;
}

/************************************************************************/

std::vector< double >&
Neuron::takeWeights() noexcept
{
	return m_weights;
}

/************************************************************************/

double
Neuron::activationFunction( double val ) noexcept
{
	return 1.0 / ( 1.0 + std::exp( -val ) );
}

/************************************************************************/

double
Neuron::calculateResult() const noexcept
{
	assert( m_connections.size() == m_weights.size() );

	std::size_t countOfNeurons = m_weights.size();
	double totalSum = 0.0;

	for (std::size_t i = 0; i < countOfNeurons; ++i)
		totalSum += m_connections[i]->getResult()
					* m_weights[i];

    return activationFunction( totalSum );
}

/************************************************************************/

template Neuron::Neuron( std::vector< Neuron* > const& );
template Neuron::Neuron( std::vector< Receptor* > const& );

/************************************************************************/
