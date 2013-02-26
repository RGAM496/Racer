#include "modelo3d.h"
#include <GL/glut.h>
#include <cmath>


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Piramide
			{


				void pyramid (GLdouble lado_base, GLdouble altura);


				void Modelo::inicializar ()
				{}


				void Modelo::finalizar ()
				{}


				void Modelo::dibujar ()
				{
					glPushMatrix();
						glScaled (1.0, escala, 1.0);
						pyramid (semilado * 2.0, altura_actual);
					glPopMatrix();
				}


				/* Funciones auxiliares. */


				void pyramid (GLdouble lado_base, GLdouble altura)
				{
					GLdouble base = lado_base / sqrt(2.0);

					glPushMatrix();
						glRotated(90,-1.0,0.0,0.0);
						glRotated(45,0.0,0.0,1.0);
						glutWireCone(base,altura,4,1);
					glPopMatrix();
				}


			}
		}
	}
}
