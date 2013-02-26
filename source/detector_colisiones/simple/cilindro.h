#ifndef CILINDRO_COLISION_H
#define CILINDRO_COLISION_H

#include "../detector_colisiones.h"
#include "../geometria_colisiones.h"


namespace urjr
{
	namespace Colisiones
	{
		namespace Objeto
		{


			class Cilindro
			: virtual public Detectable <Forma::CILINDRO>
			{

				public:

					virtual void base (Circulo *) = 0;
					virtual void altura (Intervalo &) = 0;

			};


		}
	}
}


#endif // CILINDRO_COLISION_H
