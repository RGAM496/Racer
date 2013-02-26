#include "glfw_keyboard.h"


namespace urjr
{

	// KeyboardSelector

	KeyboardHandler *KeyboardSelector::onKeyUpDownHandler = NULL;

	void KeyboardSelector::onKeyUpDownCallback (int key, int action)
	{
		onKeyUpDownHandler->onKeyUpDown (key, action);
	}

	void KeyboardSelector::setOnKeyUpDownCallbackFunction (KeyboardHandler *kbh)
	{
		onKeyUpDownHandler = kbh;
	}

	void KeyboardSelector::configure ()
	{
		glfwSetKeyCallback (onKeyUpDownCallback);
	}

	// KeyboardHandler

	void KeyboardHandler::setOnKeyUpDownCallback ()
	{
		KeyboardSelector::setOnKeyUpDownCallbackFunction (this);
	}

	void KeyboardHandler::setKeyboardCallbacks ()
	{
		setOnKeyUpDownCallback ();
	}

	// KeyboardInterface

	KeyboardInterface::KeyboardInterface ()
	{
		for (unsigned int i = 0; i < MAX_KEYS; ++i)
			keyDown[i] = false;
	}

	void KeyboardInterface::onKeyUpDown (int key, int action)
	{
		keyDown[key] = (action == GLFW_PRESS);
	}

	bool KeyboardInterface::is_down (unsigned int key)
	{
		return keyDown[key];
	}

	bool KeyboardInterface::is_up (unsigned int key)
	{
		return !keyDown[key];
	}

	inline
	bool KeyboardInterface::operator [] (unsigned int key)
	{
		return is_down (key);
	}

}
