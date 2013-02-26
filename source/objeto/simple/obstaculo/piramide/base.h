#ifndef URJR_PIRAMIDE_SIMPLE_BASE_H
#define URJR_PIRAMIDE_SIMPLE_BASE_H

#include "../../../../detector_colisiones/geometria_colisiones.h"
#include "../../../../tiempo/time.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Piramide
			{

				enum Estado
				{
					// ¡¡NO TE OLVIDES DE HACER LOS ESTADOS QUE NECESITES!!
				};


				class Base
				{
					public:
					
						Punto3D
							// Coordenada central de la base.
							centro_base;

						Longitud
							// Mitad de la longitud del lado de la figura.
							semilado,
							// Altura actual del objeto.
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


#endif // URJR_PIRAMIDE_SIMPLE_BASE_H