#include "colisiones.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cilindro
			{


				void DetectorColisiones::base (Circulo *c)
				{
					c->centro[X] = centro_base[X];
					c->centro[Y] = centro_base[Z];
					c->radio = radio_base;
				}


				void DetectorColisiones::altura (Intervalo &i)
				{
					i[MIN] = centro_base[Y];
					i[MAX] = centro_base[Y] + altura_actual;
				}


				void DetectorColisiones::getPosicionCentral (Punto3D &punto)
				{
					punto = centro_base;
				}


				void DetectorColisiones::setPosicionCentral (const Punto3D &punto)
				{
					centro_base = punto;
				}


				Longitud DetectorColisiones::ancho_maximo ()
				{
					return radio_base * 2.0;
				}


				void DetectorColisiones::zona_influencia (Intervalo &i)
				{
					i[MIN] = centro_base[Z] - radio_base;
					i[MAX] = centro_base[Z] + radio_base;
				}


			}
		}
	}
}
