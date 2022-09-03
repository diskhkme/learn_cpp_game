#pragma once

#include "raylib.h"

// Player 클래스의 정의
class Player
{
public:
	Player(const Vector2& position, const Vector2& size, const Color& color, float speed);
	void Update(float tick);
	void Draw() const;
	Vector2 GetPosition() const;

private:
	void Move(float tick);

private:
	Vector2 position;
	Vector2 size;
	Color color;
	float speed;
};