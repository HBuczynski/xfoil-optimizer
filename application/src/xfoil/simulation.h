#pragma once


#include <vector>
#include "xfoil/simulation_results.h"
//!  Class controlling execution of external simulation tools
/*!
  Controls multiple instances of xfoil optimizer running in parallel
*/
class SimulationScheduler
{
public:
private:
	const int _parallelInstances = 4;
    std::vector<Geometry*> tasks;

    //!  IO stream interface proxy for external optimizer
    /*!
      A more elaborate class description. [TODO]
    */
    class SimulationProxy
	{
		
	};
};
