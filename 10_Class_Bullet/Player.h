#pragma once

#include "raylib.h"

#include "Bullet.h"

class Player
{
private:
	Vector2 position;
	Vector2 size;
	Color color;

	Bullet* bullets[50]; // EnemyManager와 비슷한 형태로 구현할 것입니다.
	int bulletCount;
public:
	Player(float x, float y, float width, float height, Color color);
	~Player(); // 포인터 멤버가 생겼으니 소멸자를 잊지 맙시다.

	void Update();
	void Draw() const;
	Vector2 GetPosition() const;
};
