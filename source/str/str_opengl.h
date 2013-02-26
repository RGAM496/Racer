#ifndef STR_OPENGL_H
#define STR_OPENGL_H

#include "str.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


namespace str
{

	namespace glut
	{
		void BitmapString (void *font, string cadena);

		void StrokeString (void *font, string cadena);
	}
}


#endif // STR_OPENGL_H
