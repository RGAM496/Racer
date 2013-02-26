#include "textures.h"
#include "lodepng.h"
#include <iostream>
#include <map>
#include <algorithm>


namespace urjr
{
	namespace Texture
	{

		/*************************
		* Manejo de extensiones. *
		*************************/


		namespace Extension
		{


			enum Type
			{
				// Formato no válido.
				NONE,
				// Formatos válidos.
				BMP,
				PNG
			};

			//typedef bool (Image::*FileLoaderFunction) (const std::string &filename);


			std::map <std::string, Type> map = {
				{"bmp", BMP},
				{"png", PNG}
			};


			Properties properties[] = {
				{GL_NONE, GL_NONE, GL_NONE}, // NONE
				{GL_TEXTURE_2D, GL_RGB, GL_UNSIGNED_BYTE}, // BMP
				{GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE} // PNG
			};


			Image::FileLoaderFunction loader[] {
				NULL,
				&Image::load_bmp,
				&Image::load_png
			};


		}


		std::string extension (const std::string &filename);
		Extension::Type tipo_extension (const std::string &filename);


		/*****************
		* Texture::Image *
		*****************/


		// Constructores.

		Image::Image (const std::vector<unsigned char> &pixel_data, GLuint width, GLuint height, GLuint bytes_per_pixel)
		{
			set_attributes (width, height, bytes_per_pixel);
			this->pixel_data = pixel_data;
		}

		Image::Image (const unsigned char *pixel_data, GLuint width, GLuint height, GLuint bytes_per_pixel)
		{
			set_attributes (width, height, bytes_per_pixel);
			if (pixel_data) {
				unsigned int capacity = width * height * bytes_per_pixel + 1;
				this->pixel_data.reserve (capacity);
				for (unsigned int i = 0; i < capacity; ++i)
					this->pixel_data.push_back (pixel_data[i]);
			}
		}

		/*Image::Image (const Image &image)
		{
			*this = image;
		}*/


		// Comprueba si está vacía (o se cargó ya).

		bool Image::is_empty ()
		{
			return pixel_data.empty();
		}


		// Libera la imagen de la memoria. Los demás datos quedarán desfasados.

		void Image::free ()
		{
			pixel_data.clear();
		}


		// Devuelve un puntero a la cadena de caracteres del vector.

		unsigned char *Image::c_pixel_data ()
		{
			return &pixel_data[0];
		}


		// Carga una imagen desde un archivo, analizando el formato.

		bool Image::load (const std::string &filename)
		{
			Extension::Type tipo;
			FileLoaderFunction loader;

			tipo = tipo_extension (filename);

			if (tipo == Extension::Type::NONE)
				return false;

			loader = Extension::loader[tipo];

			return (this->*loader) (filename);
		}

		// Método general para abrir un archivo y leer su contenido (se especifica con qué función se leerá).

		bool Image::load (const std::string &filename, FileReaderFunction image_reader_function)
		{
			std::ifstream file;

			try {
				file.open (filename.c_str(), std::ifstream::in | std::ifstream::binary);
			} catch (...) {
				return false;
			}

			return (this->*image_reader_function) (file);
		}


		// Macro para diseñar funciones de carga de archivos.

		#define func_load_filename(func_name) 										\
		bool Image::func_name (const std::string &filename)							\
		{																			\
			return load (filename, &Image::func_name);								\
		}


		// Carga un archivo PNG.

		bool Image::load_png (const std::string &filename)
		{
			unsigned error;

			error = lodepng::decode (pixel_data, width, height, filename);

			if (error != 0)
			{
				std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
				return false;
			}

			bytes_per_pixel = 4;

			return true;
		}


		// Carga un archivo BMP.

		func_load_filename (load_bmp)

		bool Image::load_bmp (std::ifstream &file)
		{
			// AÚN EN CONSTRUCCIÓN
			return false;
		}


		// Carga un archivo que contiene la estructura.

		func_load_filename (load_struct)

		bool Image::load_struct (std::ifstream &file)
		{
			// AÚN EN CONSTRUCCIÓN
			return false;
		}


		#undef func_load_filename


		inline void Image::set_attributes (GLuint width, GLuint height, GLuint bytes_per_pixel)
		{
			this->width = width;
			this->height = height;
			this->bytes_per_pixel = bytes_per_pixel;
		}


		/*void Image::operator = (const Image &image)
		{
			width = image.width;
			height = image.height;
			bytes_per_pixel = image.bytes_per_pixel;

			pixel_data.reserve (image.pixel_data.size());
			for (unsigned int i = 0; i < pixel_data.capacity(); ++i)
				pixel_data[i] = image.pixel_data[i];
		}*/


		std::ostream& operator << (std::ostream &os, const Image &image)
		{
			os	<< "\nWidth: " << image.width
				<< "\nHeight: " << image.height
				<< "\nBytes per Pixel: " << image.bytes_per_pixel
				<< "\nImage Size: " << image.pixel_data.size()
				<< std::endl;

			return os;
		}




		/**********************
		* Texture::Properties *
		**********************/


		Properties::Properties ()
		{}


		Properties::Properties (std::initializer_list <GLenum> il)
		{
			const GLenum *v = begin(il);

			target = v[0];
			format = v[1];
			type = v[2];
		}




		/*******************
		* Texture::Manager *
		*******************/


		// Constructores.

		Manager::Manager (const std::string &filename)
		: Properties()
		{
			load_image (filename);
		}

		Manager::Manager (const Image &image, GLenum target, GLenum format, GLenum type)
		: Properties()
		{
			set_graphic_specifiers (target, format, type);
			attach_image(image);
		}

		Manager::Manager (GLenum target, GLenum format, GLenum type)
		: Properties()
		{
			set_graphic_specifiers (target, format, type);
			this->texture_id = 0;
		}

		// Destructor.

		Manager::~Manager ()
		{
			free ();
		}


		// Especifica los atributos para las funciones gráficas.

		inline void Manager::set_graphic_specifiers (GLenum target, GLenum format, GLenum type)
		{
			this->target = target;
			this->format = format;
			this->type = type;
		}


		// Genera una textura.

		void Manager::generate ()
		{
			glEnable (GL_TEXTURE_2D);
				glGenTextures (1, &texture_id);
			glDisable (GL_TEXTURE_2D);
		}


		// Libera la textura.

		void Manager::free ()
		{
			glEnable (GL_TEXTURE_2D);
				glDeleteTextures (1, &texture_id);
			glDisable (GL_TEXTURE_2D);

			image.free ();
		}


		// Indica a OpenGL que se empleará la textura.

		void Manager::bind ()
		{
			glBindTexture(target, texture_id);
		}


		// Genera un Mipmap para la textura.

		void Manager::build ()
		{
			gluBuild2DMipmaps(
				target,
				image.bytes_per_pixel,
				image.width,
				image.height,
				format,
				type,
				image.c_pixel_data ()
				);
		}


		// Crea la textura, realizando los pasos necesarios.

		void Manager::create ()
		{
			generate ();
			bind ();
			build ();
		}


		// Carga la imagen desde un archivo.

		bool Manager::load_image (const std::string &filename)
		{
			Extension::Type tipo;
			Image::FileLoaderFunction loader;

			tipo = tipo_extension (filename);

			if (tipo == Extension::Type::NONE)
				return false;

			loader = Extension::loader[tipo];

			if (! (image.*loader) (filename))
				return false;

			*this = Extension::properties[tipo];

			return true;
		}


		// Copia una imagen como si fuera propia.

		void Manager::attach_image (const Image &image)
		{
			this->image = image;
		}


		Manager & Manager::operator = (const Properties &properties)
		{
			Properties::operator = (properties);
			return *this;
		}


		/*************************
		* Manejo de extensiones. *
		*************************/


		// Devuelve la extensión de un archivo.

		std::string extension (const std::string &filename)
		{
			size_t last_dot;

			last_dot = filename.find_last_of ('.');

			return filename.substr (last_dot + 1);
		}


		// Indica el tipo de extensión, si la reconoce. Sino, devuelve NONE.

		Extension::Type tipo_extension (const std::string &filename)
		{
			std::string str_ext;
			std::map <std::string, Extension::Type> ::iterator it;

			str_ext = extension (filename);
			it = Extension::map.find (str_ext);

			if (it != Extension::map.end ())
				return it->second;

			return Extension::Type::NONE;
		}


	}
}
