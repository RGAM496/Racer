#ifndef URJR_CUBO_SIMPLE_COLISIONES_H
#define URJR_CUBO_SIMPLE_COLISIONES_H

#include "base.h"
#include "../../../objeto.h"
#include "../../../../detector_colisiones/simple/paralelepipedo.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cubo
			{


				class DetectorColisiones
				: virtual public Base
				, virtual public Colisionable
				, virtual public Colisiones::Objeto::Paralelepipedo
				{
					public:

						/* Derivadas de Colisiones::Objeto::Paralelepipedo */
						void base (Rectangulo *);
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


#endif // URJR_CUBO_SIMPLE_COLISIONES_H
