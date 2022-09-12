#include "Scene.h"

Scene::Scene()
	: sceneEntityCount{ 0 }
{
}

void Scene::UpdateScene(float tick)
{
	for (int i = 0; i < sceneEntityCount; i++)
	{
		sceneEntities[i]->Update(tick);
	}
}

void Scene::DrawScene() const
{
	for (int i = 0; i < sceneEntityCount; i++)
	{
		sceneEntities[i]->Draw();
	}
}

void Scene::AddEntity(Entity* e)
{
	sceneEntities[sceneEntityCount] = e;
	sceneEntityCount++;
}
