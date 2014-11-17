#include <iostream>
#include "gema.h"
#include <GLFW/glfw3.h>

class InputHandler : public Gema::InputListener
{
public:
	virtual void onMouseMove(double , double ) noexcept
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

	// Gema::ResourcesManager::singleton()->addFile("media/untitled.obj");
	// Gema::ResourcesManager::singleton()->addFile("media/untitled.3ds");
	// Gema::ResourcesManager::singleton()->addFile("media/untitled2.3ds");
	// Gema::ResourcesManager::singleton()->addFile("media/untitled3.3ds");
	Gema::ResourcesManager::singleton()->addFile("media/test.3ds");
	if (Gema::Engine::singleton()->init("Gema Engine"))
	{
		Gema::Input::singleton()->addListener(&input);
		if (!Gema::Engine::singleton()->start())
		{
			std::cerr << Gema::Engine::singleton()->lastError() << std::endl;
			return (2);
		}
	}
	else
	{
		std::cerr << Gema::Engine::singleton()->lastError() << std::endl;
		return (1);
	}
	return (0);
}