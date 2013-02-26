#ifndef COMPROBAR_COLISIONES_H
#define COMPROBAR_COLISIONES_H

#include "detector_colisiones.h"
#include <vector>

#ifdef DEBUG_COLISION
	#include <iostream>
	#include <typeinfo>
	#define debug(expr) std::cout << expr << std::endl
#else
	#define debug(expr) {}
#endif


namespace urjr
{
	namespace Colisiones
	{
		using std::vector;


		typedef bool (*CombrobadorColision) (Detector *, Detector *);

		extern vector<vector<CombrobadorColision>> comprobar;


		template <class DC1, class DC2>
		bool comprobar_colision (Detector *detector1, Detector *detector2)
		{
			DC1 *dc1 = dynamic_cast<DC1*> (detector1);
			DC2 *dc2 = dynamic_cast<DC2*> (detector2);

			debug ("\nComprobar colision:\n\t" << typeid(DC1).name() << "\n\t" << typeid(DC2).name() << "\n");

			return colisionan (dc1, dc2);
		}


	}
}


#undef debug

#endif // COMPROBAR_COLISIONES_H
