#ifndef PIRAMIDE_COLISION_H
#define PIRAMIDE_COLISION_H

#include "../detector_colisiones.h"
#include "../geometria_colisiones.h"


namespace urjr
{
	namespace Colisiones
	{
		namespace Objeto
		{


			class Piramide
			: virtual public Detectable <Forma::PIRAMIDE>
			{

				public:

					virtual void base (Rectangulo *) = 0;
					virtual void base (Rectangulo *, Longitud h) = 0;
					virtual void altura (Intervalo &) = 0;

			};


		}
	}
}


#endif // PIRAMIDE_COLISION_H
