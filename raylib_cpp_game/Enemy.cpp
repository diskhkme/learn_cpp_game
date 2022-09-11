#include "Enemy.h"

#include "raymath.h"

Enemy::Enemy()
	: Actor{ Vector2{0,0}, Vector2{0,0}, nullptr, 0, 0, 0, Vector2{0,0}, 0 } // 중간의 nullptr 사용에 주의하세요.
{
}

Enemy::Enemy(const Vector2& position, const Vector2& size, Texture2D* tex, int row, int col, float speed, Vector2 direction, int maxHP)
	: Actor{ position, size, tex, row, col, speed, direction, maxHP }
{
	// Enemy의 생성은 Actor에 위임합니다.
}

// Enemy의 Update는 playerPosition을 기반으로 하여 Update함수를 재정의하였습니다.
void Enemy::Update(float tick, const Vector2 & playerPosition)
{
	UpdateDirection(Vector2Normalize(Vector2Subtract(playerPosition, position))); // 플레이어 위치에 따라 방향을 바꿔주고
	Entity::Update(tick); // 그 방향에 따라 이동합니다. Entity의 Update() 함수를 직접 호출합니다.
}