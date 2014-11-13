#ifndef GEMA_RESOURCESMANAGER_H
# define GEMA_RESOURCESMANAGER_H

# include <string>
# include <vector>

namespace Gema
{
	class ResourcesManager
	{
	private:
		explicit 					ResourcesManager() = default;
		static ResourcesManager 	_singleton;
		std::vector<std::string>	_paths;

	public:
		virtual						~ResourcesManager() noexcept;

		inline void					addPath(const std::string& path) noexcept {
			this->_paths.push_back(path);
		}

		bool						load() noexcept;
	};
}

#endif