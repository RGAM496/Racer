#ifndef URJR_CUBO_SIMPLE_MODELO_H
#define URJR_CUBO_SIMPLE_MODELO_H

#include "base.h"
#include "../../../objeto.h"
#include "../../../../graphics/textures.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cubo
			{


				class Modelo
				: virtual public Base
				, virtual public Modelo3D
				{
					public:

						static Texture::Manager textura;

						static void inicializar ();
						static void finalizar ();
						void dibujar ();
				};


			}
		}
	}
}


#endif // URJR_CUBO_SIMPLE_MODELO_H
