#ifndef ESFERA_COLISION_H
#define ESFERA_COLISION_H

#include "../detector_colisiones.h"
#include "../geometria_colisiones.h"


namespace urjr
{
	namespace Colisiones
	{
		namespace Objeto
		{


			class Esfera
			: virtual public Detectable <Forma::ESFERA>
			{

				public:

					virtual void centro (Punto3D &) = 0;
					virtual Longitud radio() = 0;
					virtual void base (Circulo *) = 0;
					virtual void base (Circulo *, Longitud h) = 0;
					virtual void altura (Intervalo &) = 0;

			};


		}
	}
}


#endif // ESFERA_COLISION_H
