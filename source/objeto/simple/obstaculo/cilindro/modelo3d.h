#ifndef URJR_CILINDRO_SIMPLE_MODELO_H
#define URJR_CILINDRO_SIMPLE_MODELO_H

#include "base.h"
#include "../../../objeto.h"
#include "../../../../graphics/textures.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cilindro
			{


				class Modelo
				: virtual public Base
				, virtual public Modelo3D
				{
					public:

						static void inicializar ();
						static void finalizar ();
						void dibujar ();
				};


			}
		}
	}
}


#endif // URJR_CILINDRO_SIMPLE_MODELO_H
