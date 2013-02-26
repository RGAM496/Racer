#include "colisiones.h"

#ifdef DEBUG_POSICION
	#include <iostream>
	#define debug(expr) std::cout << expr << std::endl
	#define test(x) debug ("\t" #x " = " << x)
#else
	#define debug(expr) {}
	#define test(x) {}
#endif


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cubo
			{


				void DetectorColisiones::base (Rectangulo *r)
				{
					r->x[MIN] = centro_base[X] - semilado;
					r->x[MAX] = centro_base[X] + semilado;
					r->y[MIN] = centro_base[Z] - semilado;
					r->y[MAX] = centro_base[Z] + semilado;
				}


				void DetectorColisiones::altura (Intervalo &i)
				{
					i[MIN] = centro_base[Y];
					i[MAX] = centro_base[Y] + 2.0 * semilado;
				}


				void DetectorColisiones::getPosicionCentral (Punto3D &punto)
				{
					debug ("\nCubo - Posicion Central - Inicio");
					test (centro_base[X]);
					test (centro_base[Y]);
					test (centro_base[Z]);
					debug ("Cubo - Posicion Central - Fin\n");

					punto = centro_base;
				}


				void DetectorColisiones::setPosicionCentral (const Punto3D &punto)
				{
					centro_base = punto;
				}


				Longitud DetectorColisiones::ancho_maximo ()
				{
					return semilado * 2.0;
				}


				void DetectorColisiones::zona_influencia (Intervalo &i)
				{
					i[MIN] = centro_base[Z] - semilado;
					i[MAX] = centro_base[Z] + semilado;
				}


			}
		}
	}
}


#undef debug
#undef test