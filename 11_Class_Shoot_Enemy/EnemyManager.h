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
	void Update(Player& player); //bullet ���������� ó���ؾ� �ϴ�, player ��ü ��ü�� �޵��� �ٲ��ݽô�. bullet�� �����ϴ� ��찡 �����Ƿ�, const�� �����ݴϴ�.
	void Draw() const;

	int HandleHit(const Bullet& other); // źȯ�� ���� enemy�� index�� ��ȯ�մϴ�.
	
private:
	void HandleCollision();
	void PushCollidingObject(Enemy* self, const Enemy* const other);
	void DestroyEnemy(int index);

private:
	Enemy* enemies[50]; 
	int enemyCount;

};
