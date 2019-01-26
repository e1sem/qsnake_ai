#include "receptive_neuron.hpp"

#include <cassert>

/************************************************************************/

void
Receptor::setValue( double value ) noexcept
{
    assert( value <= 1.0 && value >= -1.0 );

    m_outputValue = value;
}

/************************************************************************/

double
Receptor::getResult() const noexcept
{
    return m_outputValue;
}

/************************************************************************/
