#pragma once

#include "raylib.h"

// Enemy 클래스의 정의. Enemy의 배열이 아니고, 각각의 개별적인 Enemy를 정의하는 클래스입니다!
// 이동 관련 함수에 Player의 위치값이 추가적으로 필요하다는 것 말고는 거의 동일합니다.
class Enemy
{
public:
	Enemy(); // Enemy 배열 생성이 가능하려면 기본 생성자가 있어야 합니다!
	Enemy(const Vector2& position, const Vector2& size, const Color& color, float speed);
	void Update(float tick, const Vector2& playerPosition);
	void Draw() const;

private:
	void Move(float tick, const Vector2& playerPosition);

private:
	Vector2 position;
	Vector2 size;
	Color color;
	float speed;
};