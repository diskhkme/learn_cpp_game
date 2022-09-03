#include "Bullet.h"

#include "raymath.h"

Bullet::Bullet()
	:Bullet{Vector2{0,0}, Vector2{0,0}, Vector2{0,0}, RED, 0.0f}
{
}

Bullet::Bullet(const Vector2 & position, const Vector2 & direction, const Vector2 & size, const Color & color, float speed)
	:position{ position }, direction{ direction }, size{ size }, color{ color }, speed{speed}
{
	// 올바른 동작을 위해서는 direction 벡터의 길이가 1이여야 합니다.
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	this->direction.x /= length;
	this->direction.y /= length;
}

void Bullet::Update(float tick)
{
	Move(tick);
}

void Bullet::Draw() const
{
	DrawCircle(position.x, position.y, size.x, color);
	DrawCircleLines(position.x, position.y, size.x, BLACK);
}

void Bullet::Move(float tick)
{
	// Bullet은 direction 방향으로 speed 속도로 날아갑니다.
	position.x += direction.x * speed * tick;
	position.y += direction.y * speed * tick;
}
