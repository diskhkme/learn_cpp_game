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

void EnemyManager::SpawnEnemy(Enemy* const enemy)
{
	enemies[enemyCount++] = enemy; // �ּҰ��� �����ϵ��� ����ȭ �սô�. Enemy�� �����ϴ� main�Լ� �κ��� ��� �ٲ������ Ȯ���ϼ���.
}

void EnemyManager::Update(Player& player)
{
	for (int i = 0; i < enemyCount; i++)
	{
		enemies[i]->Update(player.GetPosition());
	}

	for (int i = 0; i < player.GetBulletCount(); i++)
	{
		int hitEnemyIndex = HandleHit(*(player.GetBullet(i)));
		if (hitEnemyIndex != -1)
		{
			// ���� Ư�� źȯ�� enemy�� �ε����ٸ�, �ش� źȯ�� �迭���� ���� ó���մϴ�. �̰��� Player Ŭ������ ����Դϴ�.
			player.DestroyBullet(i);

			// ���� ���� �׾��ٸ�(hp�� 0 ���϶��), ���� ó���մϴ�. �̰��� EnemyManager�� ����Դϴ�.
			if (enemies[hitEnemyIndex]->GetCurrentHp() <= 0)
			{
				DestroyEnemy(hitEnemyIndex);
			}
		}
	}
	HandleCollision();
}

void EnemyManager::Draw() const
{
	for (int i = 0; i < enemyCount; i++)
	{
		enemies[i]->Draw();
	}
}

int EnemyManager::HandleHit(const Bullet& other)
{
	for (int i = 0; i < enemyCount; i++)
	{
		if (enemies[i]->CheckHit(other))
		{
			return i;
		}
	}

	return -1;
}

void EnemyManager::HandleCollision()
{
	// Enemy����� �浹 ó��
	for (int i = 0; i < enemyCount; i++)
	{
		for (int j = 0; j < enemyCount; j++)
		{
			if (i != j)
			{
				if (enemies[i]->CheckCollision(*enemies[j]))
				{
					PushCollidingObject(enemies[i], enemies[j]);
				}
			}
		}
	}
}


void EnemyManager::PushCollidingObject(Enemy* self, const Enemy* const other)
{
	Vector2 selfPosition = self->GetPosition();
	Vector2 otherPosition = other->GetPosition();

	Vector2 otherToMeDir = Vector2Normalize(Vector2Subtract(selfPosition, otherPosition));
	Vector2 otherToMeVectorAdjusted = Vector2Scale(otherToMeDir, self->GetRadius() + self->GetRadius());

	self->SetPosition(Vector2Add(otherPosition, otherToMeVectorAdjusted));
}

void EnemyManager::DestroyEnemy(int index)
{
	if (index != enemyCount - 1)
		enemies[index] = enemies[enemyCount - 1];

	enemies[enemyCount - 1] = nullptr;

	enemyCount--;
}
