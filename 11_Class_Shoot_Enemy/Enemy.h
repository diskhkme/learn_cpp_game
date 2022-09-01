#pragma once

#include "raylib.h"

#include "Bullet.h"

class Enemy
{
private:
	Vector2 position;
	float radius;
	Color color;

	int maxHp; // 적에게 HP를 부여해 줍시다. 총알에 맞으면 HP가 떨어지고, 0이 되면 죽어서 화면에서 사라지게 됩니다.
	int currentHp; // 화면에 표시하기 위해 현재 HP와 최대 HP를 따로 가지도록 하겠습니다.

public:
	Enemy(); 
	Enemy(const Vector2& position, float radius, const Color& color, int maxHp); // 추가적으로 x,y를 Vector2로 바꿔주었습니다.

	void Update(const Vector2& playerPosition);
	void Draw() const;

	bool CheckCollision(const Enemy& other);
	bool CheckHit(const Bullet& other);

	Vector2 GetPosition() const;
	void SetPosition(const Vector2& pos); 
	float GetRadius() const;
	int GetCurrentHp() const;
};
