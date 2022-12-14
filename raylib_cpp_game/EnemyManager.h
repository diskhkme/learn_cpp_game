#pragma once

#include "raylib.h"

#include "Enemy.h"

// EnemyManger, 화면에 나오는 Enemy들을 전체적으로 관리합니다.
// 우선은 기존의 main에서 관리하던 Enemy 관련 코드를 이곳으로 옮기는 형식으로 만들어보겠습니다.
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager(); // 생성된 Enemy들의 힙 메모리 주소를 담고 있으니, 소멸자에서 해제를 잊으시면 안됩니다.
		
	void SpawnEnemy(Enemy* enemy);

	void Update(float tick, const Vector2& playerPosition);
	void Draw() const;
private:
	Enemy* enemies[50];
	int enemyCount;
};