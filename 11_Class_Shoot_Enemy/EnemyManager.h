#pragma once

#include "raylib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void SpawnEnemy(Enemy* const enemy);
	void Update(Player& player); //bullet 관련정보도 처리해야 하니, player 객체 자체를 받도록 바꿔줍시다. bullet을 조작하는 경우가 있으므로, const는 떼어줍니다.
	void Draw() const;

	int HandleHit(const Bullet& other); // 탄환을 맞은 enemy의 index를 반환합니다.
	
private:
	void HandleCollision();
	void PushCollidingObject(Enemy* self, const Enemy* const other);
	void DestroyEnemy(int index);

private:
	Enemy* enemies[50]; 
	int enemyCount;

};
