#pragma once

#include "raylib.h"

class Enemy
{
private:
	Vector2 position;
	float radius;
	Color color;

public:
	Enemy(); // Enemy ���� �Ҵ� �迭�� ����� ���� �⺻ �����ڵ� ����
	Enemy(float x, float y, float radius, const Color& color);

	void Update(const Vector2& playerPosition);
	void Draw() const;

	Vector2 GetPosition() const;
	void SetPosition(const Vector2& pos); // HandleCollision�� ���� �ܺο��� ��ġ ������ �ʿ��ϱ� ������...
	float GetRadius() const;
};
