#ifndef URJR_ESFERA_SIMPLE_BASE_H
#define URJR_ESFERA_SIMPLE_BASE_H

#include "../../../../detector_colisiones/geometria_colisiones.h"
#include "../../../../tiempo/time.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Esfera
			{

				enum Estado
				{
					// ¡¡NO TE OLVIDES DE HACER LOS ESTADOS QUE NECESITES!!
				};


				class Base
				{
					public:
					
						Punto3D
							// Posición de la base de la esfera.
							centro_base;

						Longitud
							// Radio de la esfera.
							radio_cuerpo;

					protected:

						Longitud
							// Usado para el efecto de colisión.
							altura_actual;

						double
							// Escala para dibujar el objeto.
							escala;

						Time::UniformIterator <Longitud>
							// También usado para el efecto de colisión.
							iterador_altura;
				};


			}
		}
	}
}


#endif // URJR_ESFERA_SIMPLE_BASE_H