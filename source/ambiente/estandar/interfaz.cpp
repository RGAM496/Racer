#include "interfaz.h"
#include <GL/glut.h>
#include "../../str/str_opengl.h"
#include <iomanip>
#include <sstream>


namespace urjr
{
	namespace Ambiente
	{
		namespace Estandar
		{


			Interfaz::Interfaz ()
			{
				old_time = 0;
				new_time = 0;
				delta_time = 0;
				key.configure ();
				key.setKeyboardCallbacks ();
			}


			void Interfaz::avanzar_tiempo ()
			{
				old_time = new_time;
				new_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
				delta_time = new_time - old_time;
			}


			Punto3D Interfaz::transformar_coordenadas (const Punto3D &punto)
			{
				return punto;
			}


			void Interfaz::inicializar ()
			{
				static const std::string
					ruta_textura_pista = "img/ambiente/estandar/road.png";

				textura_pista.load_image (ruta_textura_pista);
				textura_pista.create ();
			}


			void Interfaz::finalizar ()
			{
				textura_pista.free ();
			}


			void Interfaz::dibujar ()
			{
				Punto3D punto;
				unsigned int numero_obstaculos;
				std::stringstream cadena;

				glClearColor(0.0,0.0,0.0,0.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				dibujar_pista ();

				vehiculo->getPosicionCentral (punto);
				punto = transformar_coordenadas (punto);
				glPushMatrix();
					glTranslated (punto[X], punto[Y], punto[Z]);
					vehiculo->dibujar();
				glPopMatrix();

				numero_obstaculos = obstaculo.size();
				for (unsigned int i = 0; i < numero_obstaculos; ++i)
				{
					obstaculo[i]->getPosicionCentral (punto);
					punto = transformar_coordenadas (punto);
					glPushMatrix();
						glTranslated (punto[X], punto[Y], punto[Z]);
						obstaculo[i]->dibujar();
					glPopMatrix();
				}


				glPushMatrix();
					glColor3d (1,1,1);
					glDisable(GL_LIGHTING);
					cadena.str("");
					cadena << "Lifes: " << vehiculo->vidas;
					glRasterPos2d(-12.0, 17.0);
					str::glut::BitmapString(GLUT_BITMAP_9_BY_15, cadena.str());
					cadena.str("");
					cadena << "Speed: " << std::fixed << std::setprecision(3) << vehiculo->velocidad;
					glRasterPos2d(-12.0, 16.5);
					str::glut::BitmapString(GLUT_BITMAP_9_BY_15, cadena.str());
					cadena.str("");
					cadena << "Time:     " << vehiculo->tiempo_recorrido;
					glRasterPos2d(8.0, 17.0);
					str::glut::BitmapString(GLUT_BITMAP_9_BY_15, cadena.str());
					cadena.str("");
					cadena << "Distance: " << vehiculo->distancia_recorrida;
					glRasterPos2d(8.0, 16.5);
					str::glut::BitmapString(GLUT_BITMAP_9_BY_15, cadena.str());
					if (vehiculo->tiempo_invencible)
					{
						cadena.str("");
						cadena << "Invincible: " << vehiculo->tiempo_invencible;
						glRasterPos2d(-2.0, 17.0);
						str::glut::BitmapString(GLUT_BITMAP_9_BY_15, cadena.str());
					}
					glEnable(GL_LIGHTING);
				glPopMatrix();
			}


			void Interfaz::dibujar_pista ()
			{
				double d, tex_l, tex_a, delta_x;

				delta_x = pista.x[MAX] - pista.x[MIN];
				d = vehiculo->distancia_recorrida / delta_x;
				d -= (int)d;
				tex_a = 1.0;
				tex_l = (pista.y[MAX] - pista.y[MIN]) / delta_x * tex_a;

				glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				textura_pista.bind();
				glBegin(GL_QUADS);
					if (vehiculo->vidas > 1)
						glColor3d (1.0, 1.0, 1.0);
					else
						glColor3d (1.0, 0.5 + 0.5 * sin(new_time), 0.5 + 0.5 * sin(new_time));

					glNormal3d(0.0,1.0,0.0);

					glTexCoord2d(0.0, 0.0 - d);
					glVertex3d (pista.x[MIN], 0.0, pista.y[MIN]);
					glTexCoord2d(0, tex_l - d);
					glVertex3d (pista.x[MIN], 0.0, pista.y[MAX]);
					glTexCoord2d(tex_a, tex_l - d);
					glVertex3d (pista.x[MAX], 0.0, pista.y[MAX]);
					glTexCoord2d(tex_a, 0.0 - d);
					glVertex3d (pista.x[MAX], 0.0, pista.y[MIN]);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}


		}
	}
}
