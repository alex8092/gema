#include <iostream>
#include "gema.h"

class InputHandler : public Gema::InputListener
{
public:
	virtual void onMouseMove(int16_t xRel, int16_t yRel) noexcept
	{
		std::cout << "mouse xrel : " << xRel << " - yrel : " << yRel << std::endl;
	}
	virtual void onMousePressed(uint8_t button) noexcept
	{
		std::cout << "Button down : " << button << std::endl;
	}

	virtual void onMouseReleased(uint8_t button) noexcept
	{
		std::cout << "Button up : " << button << std::endl;
	}

	virtual bool onKeyPressed(SDL_Scancode code) noexcept
	{
		if (code == SDL_SCANCODE_ESCAPE)
			return (false);
		return (true);
	}
	virtual bool onKeyReleased(SDL_Scancode code) noexcept
	{
		(void)code;
		return (true);
	}
};

int	main(void)
{
	InputHandler	input;
	Gema::Engine 	eng;

	Gema::ResourcesManager::singleton()->addFile("media/untitled.obj");
	Gema::ResourcesManager::singleton()->addFile("media/untitled.3ds");
	if (eng.init("Gema Engine"))
	{
		// return (0);
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