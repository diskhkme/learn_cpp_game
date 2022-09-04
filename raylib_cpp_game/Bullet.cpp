#include "Bullet.h"

#include "raymath.h"

Bullet::Bullet()
	:Bullet{Vector2{0,0}, Vector2{0,0}, Vector2{0,0}, RED, 0.0f}
{
}

Bullet::Bullet(const Vector2 & position, const Vector2 & direction, const Vector2 & size, const Color & color, float speed)
	:position{ position }, direction{ Vector2Normalize(direction) }, size{ size }, color{ color }, speed{speed}
{
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
	position = Vector2Add(position, Vector2Scale(direction, speed*tick));
}
