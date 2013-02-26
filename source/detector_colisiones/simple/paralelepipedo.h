#ifndef PARALELEPIPEDO_COLISION_H
#define PARALELEPIPEDO_COLISION_H

#include "../detector_colisiones.h"
#include "../geometria_colisiones.h"


namespace urjr
{
	namespace Colisiones
	{
		namespace Objeto
		{


			class Paralelepipedo
			: virtual public Detectable <Forma::PARALELEPIPEDO>
			{

				public:

					virtual void base (Rectangulo *) = 0;
					virtual void altura (Intervalo &) = 0;

			};


		}
	}
}


#endif // PARALELEPIPEDO_COLISION_H
