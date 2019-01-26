#include "neural_net.hpp"
#include "simple_neuron.hpp"
#include "receptive_neuron.hpp"

#include <cstdlib>
#include <cassert>
#include <fstream>

/************************************************************************/

NeuralNet::NeuralNet( topology_t const& topology )
    :    m_topology{ topology }
{
    int countOfLayers = topology.size();
    assert( countOfLayers >= 2 );

    // Receptor layer
    for ( unsigned int i = 0; i < topology[0]; ++i )
        m_receptors.push_back( new Receptor() );

    // Second layer
    m_layers.push_back( std::vector< Neuron* >() );
    for( unsigned int i = 0; i < topology[1]; ++i )
        m_layers[0].push_back( new Neuron( m_receptors ) );

    // Other layer
    for ( int i = 1; i < countOfLayers - 1; ++i )
    {
        m_layers.push_back( std::vector< Neuron* >() );
        for( unsigned int n = 0; n < topology[i+1]; ++n )
            m_layers[i].push_back( new Neuron( m_layers[i-1] ) );
    }
}

/************************************************************************/

NeuralNet::~NeuralNet()
{
    for( auto && receptor : m_receptors )
        delete receptor;

    for( auto && layer : m_layers )
        for( auto && neuron : layer )
            delete neuron;
}

/************************************************************************/

void
NeuralNet::randomizeWeights() noexcept
{
    for ( auto && layer : m_layers )
        for ( auto && neuron : layer )
            static_cast< Neuron* >( neuron )
                ->setRandomWeights();
}

/************************************************************************/

void
NeuralNet::feedForward( std::vector< double > const& input ) noexcept
{
    int countOfInputs = input.size();
    assert( countOfInputs == m_receptors.size() );
    
    for( int i = 0; i < countOfInputs; ++i )
        static_cast< Receptor* >( m_receptors[i] )
            ->setValue( input[i] );
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

NeuralNet*
NeuralNet::crossover( NeuralNet const& other )
{
    auto & topology = other.m_topology;
    assert( topology == m_topology );

    auto children = new NeuralNet( topology );

    int layersCount = m_layers.size();
    for( int l = 0; l < layersCount; ++l )
    {
        int neuronsCount = m_layers[l].size();
        for( int n = 0; n < neuronsCount; ++n )
        {
            int linksCount = m_layers[l][n]->getLinksCount();
            for( int w = 0; w < linksCount; ++w )
            {
                children->m_layers[l][n]->takeWeights()[w] =
                        std::rand() % 2
                    ?    other.m_layers[l][n]->getWeights()[w]
                    :    m_layers[l][n]->getWeights()[w];
            }

        }
    }

    return children;
}

/************************************************************************/

void
NeuralNet::mutate() noexcept
{
    int layersCount = m_layers.size();
    int layerIndex = std::rand() % layersCount;

    int neuronsCount = m_layers[layerIndex].size();
    int neuronIndex = std::rand() % neuronsCount;

    int linksCount = m_layers[layerIndex][neuronIndex]->getLinksCount();
    int linkIndex = std::rand() % linksCount;

    auto& weight = m_layers[layerIndex][neuronIndex]->takeWeights()[linkIndex];

    weight = ( std::rand() % 201 - 100 ) / 100.0;
}

/************************************************************************/

void
NeuralNet::saveToFile( std::string const& path ) const
{
    constexpr char hSeparator = ';';
    constexpr char vSeparator = '\n';

    std::ofstream fileOut;
    fileOut.open( path, std::ios_base::out );

    assert( fileOut.is_open() );

    fileOut << m_topology.size() << hSeparator;

    for( auto && count : m_topology )
        fileOut << count << hSeparator;

    fileOut << vSeparator;

    for( auto && layer : m_layers )
        for( auto && neuron : layer )
        {
            auto & weigts = neuron->getWeights();
            for( auto && weight : weigts )
                fileOut << weight << hSeparator;

            fileOut << vSeparator;
        }

    fileOut.close();
}

/************************************************************************/

NeuralNet*
NeuralNet::parseFromFile( std::string const& path )
{
    constexpr char hSeparator = ';';

    std::ifstream fileIn;
    fileIn.open( path, std::ios_base::in );
    
    assert( fileIn.is_open() );

    int topologySize;
    fileIn >> topologySize;

    topology_t topology( topologySize );
    for( int i = 0; i < topologySize; ++i )
        fileIn >> topology[i];

    auto result = new NeuralNet( topology );

    for( auto && layer : result->m_layers )
        for( auto && neuron : layer )
        {
            auto & weigts = neuron->takeWeights();
            for (auto && weight : weigts)
                fileIn >> weight;
        }

    fileIn.close();
    return result;
}

/************************************************************************/
