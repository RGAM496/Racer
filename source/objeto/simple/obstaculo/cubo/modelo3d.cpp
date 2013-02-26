#include "modelo3d.h"
#include <GL/gl.h>


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cubo
			{


				void drawCube(double semilado);

				const std::string ruta_textura = "img/objeto/simple/cubo.png";


				Texture::Manager
					Modelo::textura;


				void Modelo::inicializar ()
				{
					textura.load_image (ruta_textura);
					textura.create ();
				}


				void Modelo::finalizar ()
				{
					textura.free ();
				}


				void Modelo::dibujar ()
				{
					glPushMatrix ();
						textura.bind ();
						glEnable (GL_TEXTURE_2D);
							glScaled (1.0, escala, 1.0);
							glTranslated (0.0, semilado, 0.0);
							drawCube (semilado);
						glDisable (GL_TEXTURE_2D);
					glPopMatrix ();
				}


				/* Funciones auxiliares. */


				/** Función tomada prestada de un traumado por la optimización, como
				 *  yo, y adaptada para optimizar un poco más.
				 *  Preparado para dibujar cualquier textura se habilite previamente.
				 */
				void drawCube(double h)
				{
					// For performance, we avoid matrix operations & function calls
					// double h = size/2.0;  // Half of cube side
					double mh = -h;       // Minus h, to minimize computation

					glBegin(GL_QUADS);
						// +z face
						glNormal3d(0., 0., 1.);
						glTexCoord2d(0., 0.);
						glVertex3d(mh, mh, h);
						glTexCoord2d(1., 0.);
						glVertex3d(h, mh, h);
						glTexCoord2d(1., 1.);
						glVertex3d(h, h, h);
						glTexCoord2d(0., 1.);
						glVertex3d(mh, h, h);

						// -z face
						glNormal3d(0., 0., -1.);
						glTexCoord2d(0., 0.);
						glVertex3d(h, mh, mh);
						glTexCoord2d(1., 0.);
						glVertex3d(mh, mh, mh);
						glTexCoord2d(1., 1.);
						glVertex3d(mh, h, mh);
						glTexCoord2d(0., 1.);
						glVertex3d(h, h, mh);

						// +x face
						glNormal3d(1., 0., 0.);
						glTexCoord2d(0., 0.);
						glVertex3d(h, mh, h);
						glTexCoord2d(1., 0.);
						glVertex3d(h, mh, mh);
						glTexCoord2d(1., 1.);
						glVertex3d(h, h, mh);
						glTexCoord2d(0., 1.);
						glVertex3d(h, h, h);

						// -x face
						glNormal3d(-1., 0., 0.);
						glTexCoord2d(0., 0.);
						glVertex3d(mh, mh, mh);
						glTexCoord2d(1., 0.);
						glVertex3d(mh, mh, h);
						glTexCoord2d(1., 1.);
						glVertex3d(mh, h, h);
						glTexCoord2d(0., 1.);
						glVertex3d(mh, h, mh);

						// +y face
						glNormal3d(0., 1., 0.);
						glTexCoord2d(0., 0.);
						glVertex3d(mh, h, h);
						glTexCoord2d(1., 0.);
						glVertex3d(h, h, h);
						glTexCoord2d(1., 1.);
						glVertex3d(h, h, mh);
						glTexCoord2d(0., 1.);
						glVertex3d(mh, h, mh);

						// -y face
						glNormal3d(0., -1., 0.);
						glTexCoord2d(0., 0.);
						glVertex3d(mh, mh, mh);
						glTexCoord2d(1., 0.);
						glVertex3d(h, mh, mh);
						glTexCoord2d(1., 1.);
						glVertex3d(h, mh, h);
						glTexCoord2d(0., 1.);
						glVertex3d(mh, mh, h);
					glEnd();
				}


				/* Esta era mi función. Nótese la diferencia. */ /*
				void cubo (GLdouble lado, Texture::Manager &textura)
				{
					GLdouble pos = lado / 2;

					GLdouble vertice[][3] = {
						{-pos,0.0,+pos},
						{-pos,0.0,-pos},
						{+pos,0.0,-pos},
						{+pos,0.0,+pos},
						{-pos,lado,+pos},
						{-pos,lado,-pos},
						{+pos,lado,-pos},
						{+pos,lado,+pos},
					};

					#define V(n) glVertex3dv(vertice[n])

					glEnable(GL_TEXTURE_2D);
					textura.bind();

					glBegin(GL_QUADS);

						glNormal3d( 1.0, 0.0, 0.0);
							glTexCoord2d(0.0, 0.0); V(7);
							glTexCoord2d(0.0, 1.0); V(3);
							glTexCoord2d(1.0, 1.0); V(2);
							glTexCoord2d(1.0, 0.0); V(6);

						glNormal3d( 0.0, 1.0, 0.0);
							glTexCoord2d(0.0, 0.0); V(5);
							glTexCoord2d(0.0, 1.0); V(4);
							glTexCoord2d(1.0, 1.0); V(7);
							glTexCoord2d(1.0, 0.0); V(6);

						glNormal3d( 0.0, 0.0, 1.0);
							glTexCoord2d(0.0, 0.0); V(4);
							glTexCoord2d(0.0, 1.0); V(0);
							glTexCoord2d(1.0, 1.0); V(3);
							glTexCoord2d(1.0, 0.0); V(7);

						glNormal3d(-1.0, 0.0, 0.0);
							glTexCoord2d(0.0, 0.0); V(5);
							glTexCoord2d(0.0, 1.0); V(1);
							glTexCoord2d(1.0, 1.0); V(0);
							glTexCoord2d(1.0, 0.0); V(4);

						glNormal3d( 0.0,-1.0, 0.0);
							glTexCoord2d(0.0, 0.0); V(0);
							glTexCoord2d(0.0, 1.0); V(1);
							glTexCoord2d(1.0, 1.0); V(2);
							glTexCoord2d(1.0, 0.0); V(3);

						glNormal3d( 0.0, 0.0,-1.0);
							glTexCoord2d(0.0, 0.0); V(6);
							glTexCoord2d(0.0, 1.0); V(2);
							glTexCoord2d(1.0, 1.0); V(1);
							glTexCoord2d(1.0, 0.0); V(5);

					glEnd();

					glDisable(GL_TEXTURE_2D);

					#undef V
				}*/


			}
		}
	}
}
