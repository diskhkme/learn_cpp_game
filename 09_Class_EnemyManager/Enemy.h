#pragma once

#include "raylib.h"

class Enemy
{
private:
	Vector2 position;
	float radius;
	Color color;

public:
	Enemy(); // Enemy 동적 할당 배열을 만들기 위해 기본 생성자도 정의
	Enemy(float x, float y, float radius, const Color& color);

	void Update(const Vector2& playerPosition);
	void Draw() const;

	Vector2 GetPosition() const;
	void SetPosition(const Vector2& pos); // HandleCollision에 의해 외부에서 위치 수정이 필요하기 때문에...
	float GetRadius() const;
};
