#include "Enemy.h"

#include "raymath.h"

Enemy::Enemy()
	:Enemy{Vector2{0,0}, Vector2{0,0}, Color{0,0,0,0}, 0.0f} // 아래 생성자를 위임으로 호출
{
}

Enemy::Enemy(const Vector2 & position, const Vector2 & size, const Color & color, float speed)
	: position{ position }, size{ size }, color{ color }, speed{ speed }
{
	// 사실 적은 Circle이기 때문에 size값은 radius 하나만 필요하지만, 통일성을 위해서 그냥 Vector2 size로 받고, x값만 사용합시다.
}

void Enemy::Update(float tick, const Vector2 & playerPosition)
{
	Move(tick, playerPosition);
}

void Enemy::Draw() const
{
	DrawCircle(position.x, position.y, size.x, color);
	DrawCircleLines(position.x, position.y, size.x, BLACK);

}

void Enemy::Move(float tick, const Vector2& playerPosition)
{
	float vectorX = playerPosition.x - position.x;
	float vectorY = playerPosition.y - position.y;

	float length = sqrt(vectorX * vectorX + vectorY * vectorY);

	vectorX = vectorX / length;
	vectorY = vectorY / length;

	position.x += vectorX * speed * tick;
	position.y += vectorY * speed * tick;
}
