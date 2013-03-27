#ifndef URJR_GLFW_KEYBOARD_H
#define URJR_GLFW_KEYBOARD_H

#include <GL/glfw.h>


namespace urjr
{

	// Maneja los mensajes recibidos al pulsar o soltar teclas.
	class KeyboardHandler
	{
		public:
			void setOnKeyUpDownCallback ();
			void setKeyboardCallbacks ();
		private:
			virtual void onKeyUpDown (int key, int action) = 0;
		friend class KeyboardSelector;
	};

	// Selecciona qué función se empleará para manejar el teclado.
	class KeyboardSelector
	{
		public:
			static void setOnKeyUpDownCallbackFunction (KeyboardHandler *kbh);
			static void configure ();
		private:
			static KeyboardHandler *onKeyUpDownHandler;
			static void onKeyUpDownCallback (int key, int action);
	};

	// Manejador del teclado para una interfaz.
	class KeyboardInterface
	: virtual public KeyboardHandler
	, virtual public KeyboardSelector
	{
		public:
			static const unsigned int MAX_KEYS = GLFW_KEY_LAST + 1;
			bool is_down (unsigned int key);
			bool is_up (unsigned int key);
			bool operator [] (unsigned int); // Igual que key_down.
			KeyboardInterface ();
		protected:
			bool keyDown[MAX_KEYS];
		protected:
			virtual void onKeyUpDown (int key, int action);
	};

}



#endif // URJR_GLFW_KEYBOARD_H
