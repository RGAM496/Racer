#include "modelo3d.h"
#include <GL/glut.h>
#include <cmath>


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cilindro
			{


				void cilindro (GLdouble radio_base, GLdouble altura);


				void Modelo::inicializar ()
				{}


				void Modelo::finalizar ()
				{}


				void Modelo::dibujar ()
				{
					glPushMatrix();
						glScaled (1.0, escala, 1.0);
						cilindro (radio_base, altura_actual);
					glPopMatrix();
				}


				/* Funciones auxiliares. */


				void cilindro (GLdouble radio_base, GLdouble altura)
				{
					GLUquadric *qCilindro = gluNewQuadric();
					const GLint slices = 50;
					const GLint loops = 10;

					glPushMatrix();
						glRotated(90,-1.0,0.0,0.0);
						glNormal3d(0,0,1);
						gluQuadricOrientation(qCilindro,GLU_INSIDE);
						gluDisk(qCilindro,0,radio_base,slices,loops);
						gluQuadricOrientation(qCilindro,GLU_OUTSIDE);
						gluCylinder(qCilindro,radio_base,radio_base,altura,slices,loops);
						glTranslated(0,0,altura);
						gluDisk(qCilindro,0,radio_base,slices,loops);
					glPopMatrix();

					gluDeleteQuadric(qCilindro);
				}


			}
		}
	}
}
