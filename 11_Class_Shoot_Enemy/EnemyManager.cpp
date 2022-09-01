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
	enemies[enemyCount++] = enemy; // 주소값만 저장하도록 간략화 합시다. Enemy를 생성하는 main함수 부분이 어떻게 바뀌었는지 확인하세요.
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
			// 만일 특정 탄환이 enemy와 부딪혔다면, 해당 탄환을 배열에서 삭제 처리합니다. 이것은 Player 클래스의 기능입니다.
			player.DestroyBullet(i);

			// 만일 적이 죽었다면(hp가 0 이하라면), 삭제 처리합니다. 이것은 EnemyManager의 기능입니다.
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
	// Enemy들과의 충돌 처리
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
