#pragma once

#include "raylib.h"

// Bullet 클래스의 정의
// 마우스를 클릭하면 Bullet이 플레이어 위치에서 마우스 쪽으로 발사됩니다.
class Bullet
{
public:
	Bullet(); 
	Bullet(const Vector2& position, const Vector2& direction, const Vector2& size, const Color& color, float speed);
	void Update(float tick);
	void Draw() const;

private:
	void Move(float tick);

private:
	Vector2 position;
	Vector2 direction;
	Vector2 size;
	Color color;
	float speed;
};