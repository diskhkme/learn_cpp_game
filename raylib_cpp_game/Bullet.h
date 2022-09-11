#pragma once

#include "raylib.h"

#include "Entity.h"

// Bullet 클래스의 정의. Entity의 유도 클래스
// Bullet은 현재 생성되면 날아가기만 하면 되기 때문에 Entity와 별로 다를것이 없습니다.
class Bullet : public Entity
{
public:
	Bullet();
	Bullet(const Vector2& position, const Vector2& size, Texture2D* tex, int row, int col, float speed, Vector2 direction);

private:

};