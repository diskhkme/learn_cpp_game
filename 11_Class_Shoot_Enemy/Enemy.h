#pragma once

#include "raylib.h"

#include "Bullet.h"

class Enemy
{
private:
	Vector2 position;
	float radius;
	Color color;

	int maxHp; // ������ HP�� �ο��� �ݽô�. �Ѿ˿� ������ HP�� ��������, 0�� �Ǹ� �׾ ȭ�鿡�� ������� �˴ϴ�.
	int currentHp; // ȭ�鿡 ǥ���ϱ� ���� ���� HP�� �ִ� HP�� ���� �������� �ϰڽ��ϴ�.

public:
	Enemy(); 
	Enemy(const Vector2& position, float radius, const Color& color, int maxHp); // �߰������� x,y�� Vector2�� �ٲ��־����ϴ�.

	void Update(const Vector2& playerPosition);
	void Draw() const;

	bool CheckCollision(const Enemy& other);
	bool CheckHit(const Bullet& other);

	Vector2 GetPosition() const;
	void SetPosition(const Vector2& pos); 
	float GetRadius() const;
	int GetCurrentHp() const;
};
