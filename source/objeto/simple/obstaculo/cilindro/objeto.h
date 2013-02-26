#ifndef URJR_CILINDRO_SIMPLE_H
#define URJR_CILINDRO_SIMPLE_H

#include "base.h"
#include "colisiones.h"
#include "modelo3d.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cilindro
			{


				class Objeto
				: virtual public Base
				, virtual public DetectorColisiones
				, virtual public Modelo
				, virtual public Movil
				{
					public:

						Accion recibir_evento (Evento, double delta_tiempo, Vehiculo *);
						void desplazar (double magnitud, Direccion);
				};


			}
		}
	}
}

#endif // URJR_CILINDRO_SIMPLE_H
