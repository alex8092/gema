#ifndef GEMA_NODE_H
# define GEMA_NODE_H

# include <string>
# include <map>
# include "mat4.h"

namespace Gema
{
	class Scene;

	class Node
	{
	private:
		std::string						_name;
		mat4							_view;
		std::map<std::string, Node*>	_child_nodes;
		Scene							*_parent_scene = nullptr;
		Node							*_parent = nullptr;

	public:
		explicit 			Node(const std::string& name, Scene *parent_scene, Node *parent = nullptr);
		virtual				~Node() noexcept;

		Node 				*appendNode(const std::string& name) noexcept;
		inline Node 		*parent() noexcept {
			return (this->_parent);
		}
		Scene				*parentScene() noexcept;

		inline std::string	name() const noexcept {
			return (this->_name);
		}
	};
}

#endif