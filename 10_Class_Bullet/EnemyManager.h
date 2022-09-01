#pragma once

#include "raylib.h"
#include "Enemy.h"

// ���ӿ��� ���Ǵ� ��� Enemy��ü�� ���� ���⼭ �����˴ϴ�.
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager(); // �����͸� ����� ������ �ֱ� ������, �Ҹ��ڸ� ���� ������!

	void SpawnEnemy(const Vector2& position, float radius, const Color& color);
	void Update(const Vector2& playerPosition);
	void Draw() const;
private:
	void HandleCollision();
	void PushCollidingObject(Enemy* self, const Enemy* const other);

private:
	// (����!) ���ݱ����� Enemy���� �Ѳ����� ����������, ������ Enemy�� �ϳ��� ���� �� �ֵ��� �������� ���� ���Դϴ�.
	// ���� �� �޸𸮿� Enemy ��ü�� �ϳ��� �����ϰ�, �� �ּҸ� enemies �迭�� �ϳ��� ������ �δ� ������� �����մϴ�.
	Enemy* enemies[50]; // ���� Enemy ��ü�鿡 ���� ������ �迭. 50���� �켱 �����մϴ�.
	int enemyCount;

};
