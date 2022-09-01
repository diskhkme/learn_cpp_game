#pragma once

#include "raylib.h"

class Bullet
{
private:
	Vector2 currentPosition;
	const Vector2 shootDirection;
	float radius;
	Color color;

	float speed;
	int damage;
public:
	Bullet(const Vector2& startPosition, const Vector2& direction, float speed, int damage, float radius,  const Color& color);

	void Update();
	void Draw() const;
	Vector2 GetPosition() const;
	float GetRadius() const; // Collision check�� ���� ����Ӵϴ�.
	int GetDamage() const; // Hit Handling�� ���� ����Ӵϴ�.
};