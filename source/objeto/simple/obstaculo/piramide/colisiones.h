#ifndef URJR_PIRAMIDE_SIMPLE_COLISIONES_H
#define URJR_PIRAMIDE_SIMPLE_COLISIONES_H

#include "base.h"
#include "../../../objeto.h"
#include "../../../../detector_colisiones/simple/piramide.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Piramide
			{


				class DetectorColisiones
				: virtual public Base
				, virtual public Colisionable
				, virtual public Colisiones::Objeto::Piramide
				{
					public:

						/* Derivadas de Colisiones::Objeto::Piramide */
						void base (Rectangulo *);
						void base (Rectangulo *, Longitud h);
						void altura (Intervalo &);
						/* Derivadas de Colisionable */
						void getPosicionCentral (Punto3D &);
						void setPosicionCentral (const Punto3D &);
						Longitud ancho_maximo ();
						void zona_influencia (Intervalo &);
				};


			}
		}
	}
}


#endif // URJR_PIRAMIDE_SIMPLE_COLISIONES_H
