#pragma once

#include "raylib.h"

#include "Entity.h"

// Enemy 클래스의 정의. Entity의 유도 클래스
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(const Vector2& position, const Vector2& size, Texture2D* tex, int row, int col, float speed, Vector2 direction);

	void Update(float tick, const Vector2& playerPosition);
private:
	// 공통 데이터는 Entity가 가지고있기 때문에 모두 없애줍니다.
};