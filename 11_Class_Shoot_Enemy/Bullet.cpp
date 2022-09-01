#include "Bullet.h"

#include "raymath.h"

Bullet::Bullet(const Vector2& startPosition, const Vector2& direction, float speed, int damage, float radius, const Color& color)
	: currentPosition{ startPosition }, shootDirection{ Vector2Normalize(direction) }, radius{ radius }, speed{ speed }, color{ color }, damage{ damage }
{
}

void Bullet::Update()
{
	Vector2 moveDelta = Vector2Scale(shootDirection, speed);
	currentPosition = Vector2Add(currentPosition, moveDelta);
}

void Bullet::Draw() const
{
	DrawCircle(currentPosition.x, currentPosition.y, radius, color);
	DrawCircleLines(currentPosition.x, currentPosition.y, radius, BLACK);
}

Vector2 Bullet::GetPosition() const
{
	return currentPosition;
}

float Bullet::GetRadius() const
{
	return radius;
}

int Bullet::GetDamage() const
{
	return damage;
}