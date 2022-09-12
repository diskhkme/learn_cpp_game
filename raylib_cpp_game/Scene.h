#pragma once

#include "Entity.h"

class Scene
{
public:
	Scene();

	void UpdateScene(float tick);
	void DrawScene() const;

	void AddEntity(Entity* e);

private:
	Entity* sceneEntities[100];
	int sceneEntityCount;

};