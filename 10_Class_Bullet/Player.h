#pragma once

#include "raylib.h"

#include "Bullet.h"

class Player
{
private:
	Vector2 position;
	Vector2 size;
	Color color;

	Bullet* bullets[50]; // EnemyManager�� ����� ���·� ������ ���Դϴ�.
	int bulletCount;
public:
	Player(float x, float y, float width, float height, Color color);
	~Player(); // ������ ����� �������� �Ҹ��ڸ� ���� ���ô�.

	void Update();
	void Draw() const;
	Vector2 GetPosition() const;
};
