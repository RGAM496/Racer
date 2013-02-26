#include "modelo3d.h"
#include <GL/glut.h>


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Esfera
			{


				void Modelo::inicializar ()
				{}


				void Modelo::finalizar ()
				{}


				void Modelo::dibujar ()
				{
					glPushMatrix ();
						glScaled (escala, escala, escala);
						glTranslated (0.0, radio_cuerpo, 0.0);
						glutSolidSphere (radio_cuerpo, 50, 50);
					glPopMatrix ();
				}

			}
		}
	}
}
