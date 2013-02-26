#include <cstdlib>
#include <iostream>
#include <GL/glfw.h>
//#include "../objeto.h"
/*#include "../simple/obstaculo/cubo/objeto.h"
#include "../simple/obstaculo/piramide/objeto.h"
#include "../simple/obstaculo/cilindro/objeto.h"*/
#include "objeto/simple/obstaculos.h"
#include "objeto/simple/vehiculo/cajita/objeto.h"
#include "objeto/generador_objetos.h"
#include "ambiente/estandar/reglas.h"
#include "str/str_opengl.h"


using namespace std;
using namespace urjr;

ostream & operator << (ostream &os, const Punto3D &p)
{
	os << '(' << p[0] << ", " << p[1] << ", " << p[2] << ')';
	return os;
}


void dibujar_ejes (Punto3D p, double largo = 2)
{
	glBegin(GL_LINES);
		// Eje X.
		glColor3d (1,0,0);
		glVertex3d (p[X], p[Y], p[Z]);
		glVertex3d (p[X]+largo, p[Y], p[Z]);
		// Eje Y.
		glColor3d (0,1,0);
		glVertex3d (p[X], p[Y], p[Z]);
		glVertex3d (p[X], p[Y]+largo, p[Z]);
		// Eje Z.
		glColor3d (0,0,1);
		glVertex3d (p[X], p[Y], p[Z]);
		glVertex3d (p[X], p[Y], p[Z]+largo);
	glEnd();
}


void glTranslated (Punto3D p)
{
	glTranslated (p[X], p[Y], p[Z]);
}


int main ()
{
	bool running = true;
	GLFWvidmode vDesktop;

	if (!glfwInit ())
		exit (EXIT_FAILURE);

	//glfwGetDesktopMode(&vDesktop);
	vDesktop.Width = 1024;
	vDesktop.Height = 768;
	if (!glfwOpenWindow (vDesktop.Width,vDesktop.Height, 0,0,0,0,0,0, GLFW_WINDOW))//GLFW_FULLSCREEN))
	{
		glfwTerminate ();
		return EXIT_FAILURE;
	}
	glfwSetWindowPos (800, 100);

	const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

	const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_LINE_SMOOTH);

	glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);



	bool jugar = true;
    Ambiente::Estandar::Reglas r;
    Objeto::GeneradorVehiculoEspecifico <Objeto::Simple::Cajita::Objeto> genCajita;
    bool old_m = false, key_m, motion_blur = false;

    //Objeto::Simple::cubo_verde.inicializar();
    //auto cubo = Objeto::Simple::cubo_verde.generate();

    r.cargar_vehiculo(&genCajita);
    r.inicializar();
    //Punto3D punto;
    //r.vehiculo->getPosicionCentral(punto);




	while (running)
	{
		//glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //gluPerspective( 65.0f, (GLfloat)640/(GLfloat)480, 1.0f, 100.0f );
        const float ar = 4.0/3.0; //vDesktop.Width / vDesktop.Height;
        glViewport(0, 0, vDesktop.Width, vDesktop.Height);
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum(-ar, ar, -1.0, 1.0, 2.0, 200.0);
        //glOrtho(0, vDesktop.Width, 0, vDesktop.Height, -1, 1);

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        gluLookAt(
			0.0, 10.0, 20.0,
			0.0, 0.0, -80.0,
			0.0, 1.0, 0.0);
		/*gluLookAt(5.0f, 4.0f, 12.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f );*/
		//glTranslated (0.0, -2.0, 0.0);


		if (jugar)
		{
			jugar = r.jugar();
		}

		r.dibujar();



		key_m = r.key.is_down('M');
		if (key_m && !old_m)
		{
			motion_blur ^= 1;
			old_m = true;
		}
		else if (!key_m && old_m)
		{
			old_m = false;
		}

		if (motion_blur)
		{
			float q = 0.70;
			glAccum(GL_MULT, q);
			glAccum(GL_ACCUM, 1-q);
			glAccum(GL_RETURN, 1.0);

			glDisable(GL_LIGHTING);
			glRasterPos2d(-12.0, 15.5);
			str::glut::BitmapString(GLUT_BITMAP_9_BY_15, "[Motion Blur]");
			glEnable(GL_LIGHTING);
		}



		glfwSwapBuffers ();

		running = !glfwGetKey (GLFW_KEY_ESC) && glfwGetWindowParam (GLFW_OPENED);
	}

	while (running)
	{
		glfwPollEvents ();
		running = !glfwGetKey (GLFW_KEY_ESC) && glfwGetWindowParam (GLFW_OPENED);
	}

	r.finalizar();
	glfwTerminate ();

	return EXIT_SUCCESS;
}
