#include "node.h"
#include "scene.h"

using Gema::Node;
using Gema::Scene;

Node::Node(const std::string& name, Scene *parent_scene, Node *parent) :
	_name(name),
	_parent_scene(parent_scene),
	_parent(parent)
{

}

Node::~Node() noexcept
{
	for (auto it : this->_child_nodes)
		delete (it.second);
}

Node*	Node::appendNode(const std::string& name) noexcept
{
	auto it = this->_child_nodes.find(name);
	if (it != this->_child_nodes.end())
		return (nullptr);
	auto n = new Node(name, this->_parent_scene, this);
	this->_child_nodes[name] = n;
	return (n);
}

Scene 	*Node::parentScene() noexcept {
	return (this->_parent_scene);
}