#ifndef URJR_INTERFAZ_AMBIENTE_ESTANDAR_H
#define URJR_INTERFAZ_AMBIENTE_ESTANDAR_H

#include "base.h"
#include "../../detector_colisiones/geometria_colisiones.h"
#include "../../menu/menu.h"
#include "../../graphics/textures.h"


namespace urjr
{
	namespace Ambiente
	{
		namespace Estandar
		{


			class Interfaz
			: virtual public Base
			, virtual public Menu
			{
				public:

					Interfaz ();

					// Actualiza las variables de control de tiempo.
					void avanzar_tiempo ();

					// Transforma las coordenadas de los puntos a una adecuada para el dibujo.
					Punto3D transformar_coordenadas (const Punto3D &);

					// Heredados de 'Menu'.
					void inicializar ();
					void finalizar ();
					void dibujar ();

					void dibujar_pista ();

				protected:

					Texture::Manager
						textura_pista;
			};


		}
	}
}


#endif // URJR_INTERFAZ_AMBIENTE_ESTANDAR_H
