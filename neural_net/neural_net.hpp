#ifndef QSNAKE_NEURALNET_NEURALNET_HPP_
#define QSNAKE_NEURALNET_NEURALNET_HPP_

/************************************************************************/

#include <string>
#include <vector>

/************************************************************************/

class Receptor;
class Neuron;

/************************************************************************/

class NeuralNet
{

/************************************************************************/

public:

/************************************************************************/

    using topology_t = std::vector< unsigned int >;

/************************************************************************/

    NeuralNet( topology_t const& topology );

    ~NeuralNet();

/************************************************************************/

    void randomizeWeights() noexcept;

    void feedForward( std::vector< double > const& input ) noexcept;

    std::vector< double > getResults() const noexcept;

/************************************************************************/

    void mutate() noexcept;

    NeuralNet* crossover( NeuralNet const& other );

/************************************************************************/

    void saveToFile( std::string const& path ) const;

    static NeuralNet* parseFromFile( std::string const& path );

/************************************************************************/

private:

/************************************************************************/

    topology_t m_topology;

    std::vector< Receptor* > m_receptors;

    std::vector< std::vector< Neuron* > > m_layers;

/************************************************************************/

};

/************************************************************************/

#endif // QSNAKE_NEURALNET_NEURALNET_HPP_
