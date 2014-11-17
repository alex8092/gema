#ifndef GEMA_RESOURCESMANAGER_H
# define GEMA_RESOURCESMANAGER_H

# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <iostream>

namespace Gema
{
	class ResourcesManager
	{
	private:
		explicit 					ResourcesManager() = default;
		static ResourcesManager 	_singleton;
		std::vector<std::string>	_paths;
		std::vector<std::string>	_files;

	public:
		virtual							~ResourcesManager() noexcept;

		static inline ResourcesManager 	*singleton() noexcept {
			return (&ResourcesManager::_singleton);
		}

		inline void						addPath(const std::string& path) noexcept {
			this->_paths.push_back(path);
		}

		inline void						addFile(const std::string& file) noexcept {
			this->_files.push_back(file);
		}

		bool							load() noexcept;
	};
}

#endif