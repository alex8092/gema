#include "engine.h"
#include "renderer.h"
#include "input.h"

using Gema::Engine;
using Gema::Window;
using Gema::ResourcesManager;
using Gema::Renderer;
using Gema::Input;

Engine			Engine::_singleton;

Engine::Engine()
{

}

bool	Engine::init(const std::string& appName, bool fullscreen) noexcept
{
	if (!this->_win)
	{
		this->_win = new Window(appName, fullscreen);
		if (!this->_win->show())
			return (false);
		Input::singleton()->setCursorVisible(false);
		Input::singleton()->setGrabCursor();
		Input::singleton()->addListener(Renderer::singleton()->camera());
		ResourcesManager::singleton()->load();
	}
	return (true);
}

bool	Engine::start() noexcept
{
	while (!this->_win->isClose())
	{
		if (!Input::singleton()->capture() || !this->_win->update())
			this->_win->close();
	}
	return (true);
}