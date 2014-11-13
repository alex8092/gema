#ifndef GEMA_ENGINE_H
# define GEMA_ENGINE_H

# include "window.h"
# include "renderer.h"
# include "input.h"
# include <stdint.h>
# include <string>

namespace Gema
{
	class Engine
	{
	private:
		Window		*_win = nullptr;
		Input		_input;
		Renderer	_render;
		std::string	_error;

	public:
		explicit 			Engine();
		virtual				~Engine() noexcept = default;

		inline void			setError(const std::string& error) noexcept {
			this->_error = error;
		}

		inline std::string	lastError() const noexcept {
			return (this->_error);
		}

		inline Renderer 	*render() noexcept {
			return (&this->_render);
		}

		inline Input		*input() noexcept {
			return (&this->_input);
		}

		bool				init(const std::string& appName) noexcept;
		bool				start() noexcept;
	};
}

#endif
