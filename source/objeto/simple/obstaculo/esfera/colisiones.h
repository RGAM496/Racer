#ifndef URJR_ESFERA_SIMPLE_COLISIONES_H
#define URJR_ESFERA_SIMPLE_COLISIONES_H

#include "base.h"
#include "../../../objeto.h"
#include "../../../../detector_colisiones/simple/esfera.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Esfera
			{


				class DetectorColisiones
				: virtual public Base
				, virtual public Colisionable
				, virtual public Colisiones::Objeto::Esfera
				{
					public:

						/* Derivadas de Colisiones::Objeto::Esfera */
						void centro (Punto3D &);
						Longitud radio();
						void base (Circulo *);
						void base (Circulo *, Longitud h);
						void altura (Intervalo &);
						/* Derivadas de Colisionable */
						void getPosicionCentral (Punto3D &);
						void setPosicionCentral (const Punto3D &);
						Longitud ancho_maximo ();
						void zona_influencia (Intervalo &);
						bool puede_colisionar ();
				};


			}
		}
	}
}


#endif // URJR_ESFERA_SIMPLE_COLISIONES_H
