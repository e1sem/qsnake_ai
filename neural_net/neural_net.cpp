#include "neural_net.hpp"
#include "receptive_neuron.hpp"
#include "simple_neuron.hpp"

#include <cassert>

/************************************************************************/

NeuralNet::NeuralNet( topology_t const& _topology )
{
	std::size_t countOfLayers = _topology.size();
	assert( countOfLayers >= 2 );

	// Receptor layer
	m_layers.push_back( INeuron::Layer() );
	for( std::size_t i = 0; i < _topology[0]; ++i )
		m_layers.front().push_back( new Receptor() );

	// Other layers
	for( std::size_t i = 1; i < countOfLayers; ++i )
	{
		m_layers.push_back( INeuron::Layer() );
		for( std::size_t n = 0; n < _topology[i]; ++n )
			m_layers[i].push_back( new Neuron( m_layers[i-1] ) );
	}
}

/************************************************************************/

NeuralNet::~NeuralNet()
{
	for( auto && layer : m_layers )
		for( auto && neuron : layer )
			delete neuron;
}

/************************************************************************/

void
NeuralNet::randomizeWeights() noexcept
{
	std::size_t countOfLayers = m_layers.size();
	for( std::size_t i = 1; i < countOfLayers; ++i )
		for( auto && neuron : m_layers[i] )
			static_cast< Neuron* >( neuron )
				->setRandomWeights();
}

/************************************************************************/

void
NeuralNet::feedForward( std::vector< double > const& _input ) noexcept
{
	auto & inputLayer = m_layers.front();
	assert( _input.size() == inputLayer.size() );

	std::size_t countOfInputs = inputLayer.size();
	for( std::size_t i = 0; i < countOfInputs; ++i )
		static_cast< Receptor* >( inputLayer[i] )
			->setResult( _input[i] );
}

/************************************************************************/

std::vector< double >
NeuralNet::getResults() const noexcept
{
	std::vector< double > result;

	for( auto && reaction : m_layers.back() )
		result.push_back( reaction->getResult() );

	return result;
}

/************************************************************************/
