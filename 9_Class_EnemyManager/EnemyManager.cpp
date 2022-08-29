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
	// �켱 ������ �� Enemy���� ������ ������ �����մϴ�.
	for (int i = 0; i < enemyCount; i++)
	{
		enemies[i]->Update(playerPosition);
	}

	// Enemy������ Collision�� HandleCollision �Լ��� �����߽��ϴ�.
	// HandleCollision�� �ܺο��� ���� ȣ���� �ʿ䰡 �����ϴ�. private ����Լ��Դϴ�.
	HandleCollision();
}

void EnemyManager::Draw() const
{
	// ������ �� Enemy���� ȭ�鿡 �׸��ϴ�.
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
				// �츮�� ������� �Լ� ���, ���̺귯������ �����ϴ� �Լ��� ����սô�.
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
