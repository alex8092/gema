#include <iostream>
#include "gema.h"

class InputHandler : public Gema::InputListener
{
public:
	virtual void onMouseMove(int16_t , int16_t ) noexcept
	{
		// std::cout << "mouse xrel : " << xRel << " - yrel : " << yRel << std::endl;
	}
	virtual void onMousePressed(uint8_t ) noexcept
	{
		// std::cout << "Button down : " << button << std::endl;
	}

	virtual void onMouseReleased(uint8_t ) noexcept
	{
		// std::cout << "Button up : " << button << std::endl;
	}

	virtual bool onKeyPressed(int code) noexcept
	{
		if (code == GLFW_KEY_ESCAPE)
			return (false);
		return (true);
	}
	virtual bool onKeyReleased(int ) noexcept
	{
		return (true);
	}
};

int	main(void)
{
	InputHandler	input;
	Gema::Engine 	eng;

	Gema::ResourcesManager::singleton()->addFile("media/untitled.obj");
	Gema::ResourcesManager::singleton()->addFile("media/untitled.3ds");
	Gema::ResourcesManager::singleton()->addFile("media/untitled2.3ds");
	Gema::ResourcesManager::singleton()->addFile("media/untitled3.3ds");
	if (eng.init("Gema Engine"))
	{
		eng.input()->addListener(&input);
		if (!eng.start())
		{
			std::cerr << eng.lastError() << std::endl;
			return (2);
		}
	}
	else
	{
		std::cerr << eng.lastError() << std::endl;
		return (1);
	}
	return (0);
}