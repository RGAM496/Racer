#ifndef URJR_CAJITA_SIMPLE_H
#define URJR_CAJITA_SIMPLE_H

#include "base.h"
#include "colisiones.h"
#include "modelo3d.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cajita
			{


				class Objeto
				: virtual public Base
				, virtual public DetectorColisiones
				, virtual public Modelo
				, virtual public Vehiculo
				{
					public:

						Accion recibir_evento (Evento, double delta_tiempo, Vehiculo *);
						void desplazar (double magnitud, Direccion);

						Objeto ();
				};


			}
		}
	}
}

#endif // URJR_CAJITA_SIMPLE_H
