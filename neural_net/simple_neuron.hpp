#ifndef QSNAKE_NEURALNET_NEURON_HPP_
#define QSNAKE_NEURALNET_NEURON_HPP_

/************************************************************************/

#include "base_neuron.hpp"

/************************************************************************/

class Neuron
    :   public INeuron
{

/************************************************************************/

public:

/************************************************************************/

    template< typename T >
    Neuron( T const& previous );

/************************************************************************/

	double getResult() const noexcept override;

    void setRandomWeights() noexcept;

	int getLinksCount() const noexcept;

/************************************************************************/

    std::vector< double > const& getWeights() const noexcept;

	std::vector< double > & takeWeights() noexcept;

/************************************************************************/

private:

/************************************************************************/

    static double activationFunction( double val ) noexcept;

    inline double calculateResult() const noexcept;

/************************************************************************/

	std::vector< const INeuron* > m_connections;

	std::vector< double > m_weights;

/************************************************************************/

}; // class Neuron

/************************************************************************/

#endif // QSNAKE_NEURALNET_NEURON_HPP_
