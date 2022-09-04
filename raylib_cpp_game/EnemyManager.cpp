#include "EnemyManager.h"

EnemyManager::EnemyManager()
	: enemyCount{ 0 }
{
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < enemyCount; i++)
	{
		delete enemies[i];
	}
}

void EnemyManager::SpawnEnemy(Enemy * enemy)
{
	//enemy의 힙 메모리 주소가 인자로 들어오면, 멤버변수 배열인 enemies에 저장하고, count를 조정합니다.
	enemies[enemyCount] = enemy;
	enemyCount++;
}

void EnemyManager::Update(float tick, const Vector2& playerPosition)
{
	// 내가 관리하고있는 모든 enemy들의 Update를 호출합니다.
	for (int i = 0; i < enemyCount; i++)
	{
		enemies[i]->Update(tick, playerPosition);
	}
}

void EnemyManager::Draw() const
{
	// 내가 관리하고있는 모든 enemy들의 Draw를 호출합니다.
	for (int i = 0; i < enemyCount; i++)
	{
		enemies[i]->Draw();
	}
}
