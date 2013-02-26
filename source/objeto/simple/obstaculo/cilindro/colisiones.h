#ifndef URJR_CILINDRO_SIMPLE_COLISIONES_H
#define URJR_CILINDRO_SIMPLE_COLISIONES_H

#include "base.h"
#include "../../../objeto.h"
#include "../../../../detector_colisiones/simple/cilindro.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cilindro
			{


				class DetectorColisiones
				: virtual public Base
				, virtual public Colisionable
				, virtual public Colisiones::Objeto::Cilindro
				{
					public:

						/* Derivadas de Colisiones::Objeto::Cilindro */
						void base (Circulo *);
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


#endif // URJR_CILINDRO_SIMPLE_COLISIONES_H
