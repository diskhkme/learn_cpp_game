#include "Enemy.h"

#include "raymath.h"

Enemy::Enemy()
	: Enemy{ 0,0,0,BLACK }
{}

Enemy::Enemy(float x, float y, float radius, Color color)
	: position{ Vector2{x,y} }, radius{ radius }, color{ color }
{}

void Enemy::Update(const Vector2& playerPosition)
{
	// 기존 UpdateEnemy에서는 다른 Enemy의 위치를 참조하여 충돌하는 경우 자신의 위치를 조정했습니다.
	// 하지만 여기서는 우선 플레이어를 따라가는 기본 위치 이동 로직만 가지도록 만들고,
	// 충돌 관련한 부분은 여전히 Main.cpp 내의 UpdateEnemy가 처리하도록 했습니다.
	// 이후 추가적으로 구조를 바꾸는 것을 해 보겠습니다.

	Vector2 enemyToPlayerVector = Vector2Subtract(playerPosition, position);
	Vector2 enemyToPlayerDirection = Vector2Normalize(enemyToPlayerVector);

	position.x += enemyToPlayerDirection.x;
	position.y += enemyToPlayerDirection.y;
}

void Enemy::Draw() const
{
	DrawCircle(position.x, position.y, radius, color);
	DrawCircleLines(position.x, position.y, radius, BLACK);
}

Vector2 Enemy::GetPosition() const
{
	return position;
}

void Enemy::SetPosition(Vector2 pos)
{
	position = pos;
}

float Enemy::GetRadius() const
{
	return radius;
}
