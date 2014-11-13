#ifndef GEMA_SCENE_H
# define GEMA_SCENE_H

# include <string>
# include "node.h"

namespace Gema
{
	class Scene
	{
	private:
		Node			_root_node;

	public:
		explicit		Scene();
		virtual 		~Scene() noexcept;

		inline Node*	rootNode() noexcept {
			return (&this->_root_node);
		}
	};
}

#endif