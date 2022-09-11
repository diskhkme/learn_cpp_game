#pragma once

#include "Entity.h"

// Actor는 체력을 갖는 Entity입니다. Player와 Enemy는 Actor이고, Bullet은 Entity입니다.
class Actor : public Entity
{
public:
	Actor(const Vector2& position, const Vector2& size, Texture2D* tex, int row, int col, float speed, Vector2 direction, int maxHP);

	void Draw() const; // 체력을 가진 객체는, HP를 화면에 표시해야 합니다.
private:
	void DrawHpBar() const;

private:
	int maxHP;
	int currentHP;
};