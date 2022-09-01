#pragma once

#include "raylib.h"
#include "Enemy.h"

// 게임에서 사용되는 모든 Enemy객체는 이제 여기서 관리됩니다.
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager(); // 포인터를 멤버로 가지고 있기 때문에, 소멸자를 잊지 마세요!

	void SpawnEnemy(const Vector2& position, float radius, const Color& color);
	void Update(const Vector2& playerPosition);
	void Draw() const;
private:
	void HandleCollision();
	void PushCollidingObject(Enemy* self, const Enemy* const other);

private:
	// (주의!) 지금까지는 Enemy들을 한꺼번에 생성했지만, 이제는 Enemy를 하나씩 만들 수 있도록 자유도를 높일 것입니다.
	// 따라서 힙 메모리에 Enemy 객체를 하나씩 생성하고, 그 주소를 enemies 배열에 하나씩 저장해 두는 방식으로 구현합니다.
	Enemy* enemies[50]; // 실제 Enemy 객체들에 대한 포인터 배열. 50개로 우선 가정합니다.
	int enemyCount;

};
