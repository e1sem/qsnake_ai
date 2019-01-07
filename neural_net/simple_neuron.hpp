#ifndef __SIMPLE_NEURON_HPP__
#define __SIMPLE_NEURON_HPP__

/************************************************************************/

#include "neural_net/base_neuron.hpp"

/************************************************************************/

class Neuron
	: public INeuron
{

/************************************************************************/

public:

/************************************************************************/

	Neuron( Layer const& _previous );

/************************************************************************/

	double getResult() const noexcept override;

/************************************************************************/

	void setRandomWeights() noexcept;

/************************************************************************/

private:

/**********************************************************************/

	static double activationFunction( double val ) noexcept;

	inline double calculateResult() const noexcept;

/**********************************************************************/

	std::vector< const INeuron* > m_connections;

	std::vector< double > m_weights;

/**********************************************************************/

}; // class Neuron

/**********************************************************************/

#endif // __SIMPLE_NEURON_HPP__