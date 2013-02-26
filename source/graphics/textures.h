#ifndef TEXTURES_H
#define TEXTURES_H


#include <GL/glut.h>
#include <vector>
#include <string>
#include <fstream>
#include <initializer_list>


// Manejador de texturas en OpenGL + GLUT.


namespace urjr
{
	namespace Texture
	{


		class Image {

			public:

				typedef bool (Image::*FileLoaderFunction) (const std::string &);
				typedef bool (Image::*FileReaderFunction) (std::ifstream &);

				GLuint width;
				GLuint height;
				GLuint bytes_per_pixel; // 2:RGB16, 3:RGB, 4:RGBA
				std::vector<unsigned char> pixel_data;

				Image (
					const std::vector<unsigned char> &pixel_data,
					GLuint width = 0,
					GLuint height = 0,
					GLuint bytes_per_pixel = 0
				);
				Image (
					const unsigned char *pixel_data = NULL,
					GLuint width = 0,
					GLuint height = 0,
					GLuint bytes_per_pixel = 0
				);
				/*Image (
					const Image &Image
				);*/

				bool is_empty ();
				void free ();

				unsigned char *c_pixel_data ();

				bool load (const std::string &filename);
				bool load (const std::string &filename, FileReaderFunction image_reader_function);
				bool load_png (const std::string &filename);
				bool load_bmp (const std::string &filename);
				bool load_struct (const std::string &filename);

				//bool load_png (std::ifstream &file);
				bool load_bmp (std::ifstream &file);
				bool load_struct (std::ifstream &file);

			private:

				void set_attributes (GLuint width, GLuint height, GLuint bytes_per_pixel);
		};


		std::ostream& operator << (std::ostream &os, const Image &image);


		class Properties {

			protected:

				GLenum target;
				GLenum format;
				GLenum type;

			public:

				Properties ();
				Properties (std::initializer_list <GLenum>);
		};


		class Manager
		: virtual public Properties {

			private:

				Image image;
				GLuint texture_id;

				/*
				GLenum target;
				GLenum format;
				GLenum type;
				*/

				void set_graphic_specifiers (GLenum target, GLenum format, GLenum type);


			public:

				Manager (
					const std::string &filename
				);
				Manager (
					const Image &image,
					GLenum target = GL_TEXTURE_2D,
					GLenum format = GL_RGB,
					GLenum type = GL_UNSIGNED_BYTE
				);
				Manager (
					GLenum target = GL_TEXTURE_2D,
					GLenum format = GL_RGB,
					GLenum type = GL_UNSIGNED_BYTE
				);
				~Manager ();

				void generate ();
				void free ();
				void bind ();
				void build ();

				void create ();

				bool load_image (const std::string &filename);
				void attach_image (const Image &image);

				// Operadores.
				Manager & operator = (const Properties &);
		};


	}
}


#endif // TEXTURES_H
