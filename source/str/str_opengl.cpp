#include "str_opengl.h"

namespace str
{
	namespace glut
	{

		typedef void (__attribute__((__stdcall__)) *f_print_character) (void *font, int character);

		void PrintString (void *font, string cadena, f_print_character fpc);


		void BitmapString (void *font, string cadena)
		{
			PrintString (font, cadena, glutBitmapCharacter);
		}

		void StrokeString (void *font, string cadena)
		{
			PrintString (font, cadena, glutStrokeCharacter);
		}


		void PrintString (void *font, string cadena, f_print_character fpc)
		{
			size_t l = cadena.length();

			for (size_t i = 0; i < l; ++i)
				fpc (font, cadena[i]);
		}
	}
}
