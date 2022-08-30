#include "EnemyManager.h"

#include "raymath.h"

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

void EnemyManager::SpawnEnemy(Vector2 position, float radius, const Color & color)
{
	enemies[enemyCount] = new Enemy{ position.x, position.y, radius, color };
	enemyCount++;
}

void EnemyManager::Update(const Vector2& playerPosition)
{
	// 우선 생성된 각 Enemy들의 움직임 로직을 실행합니다.
	for (int i = 0; i < enemyCount; i++)
	{
		enemies[i]->Update(playerPosition);
	}

	// Enemy끼리의 Collision은 HandleCollision 함수에 구현했습니다.
	// HandleCollision은 외부에서 직접 호출할 필요가 없습니다. private 멤버함수입니다.
	HandleCollision();
}

void EnemyManager::Draw() const
{
	// 생성된 각 Enemy들을 화면에 그립니다.
	for (int i = 0; i < enemyCount; i++)
	{
		enemies[i]->Draw();
	}
}

void EnemyManager::HandleCollision()
{
	for (int i = 0; i < enemyCount; i++)
	{
		for (int j = 0; j < enemyCount; j++)
		{
			if (i != j)
			{
				// 우리가 만들었던 함수 대신, 라이브러리에서 제공하는 함수를 사용합시다.
				if (CheckCollisionCircles(enemies[i]->GetPosition(), enemies[i]->GetRadius(), enemies[j]->GetPosition(), enemies[j]->GetRadius()))
				{
					PushCollidingObject(enemies[i], enemies[j]);
				}
			}

		}
	}
}

void EnemyManager::PushCollidingObject(Enemy* self, Enemy* other)
{
	Vector2 selfPosition = self->GetPosition();
	Vector2 otherPosition = other->GetPosition();

	Vector2 otherToMeDir = Vector2Normalize(Vector2Subtract(selfPosition, otherPosition));
	Vector2 otherToMeVectorAdjusted = Vector2Scale(otherToMeDir, self->GetRadius() + self->GetRadius());

	self->SetPosition(Vector2Add(otherPosition, otherToMeVectorAdjusted));
}
