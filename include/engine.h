#ifndef GEMA_ENGINE_H
# define GEMA_ENGINE_H

# include "window.h"
# include "resourcesmanager.h"
# include <stdint.h>
# include <string>

namespace Gema
{
	class Engine
	{
	private:
		Window					*_win = nullptr;
		std::string				_error;
		explicit 				Engine();
		static Engine			_singleton;

	public:
		virtual					~Engine() noexcept = default;

		static inline Engine	*singleton() noexcept {
			return (&Engine::_singleton);
		}

		inline void				setError(const std::string& error) noexcept {
			this->_error = error;
		}

		inline std::string		lastError() const noexcept {
			return (this->_error);
		}

		inline Window 			*window() noexcept {
			return (this->_win);
		}

		bool					init(const std::string& appName, bool fullscreen = false) noexcept;
		bool					start() noexcept;
	};
}

#endif
