#include "scene.h"

using Gema::Scene;

Scene::Scene() :
	_root_node("root", this)
{

}

Scene::~Scene() noexcept
{

}