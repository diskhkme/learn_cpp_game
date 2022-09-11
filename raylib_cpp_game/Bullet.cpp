#include "Bullet.h"

#include "raymath.h"

Bullet::Bullet()
	: Entity{ Vector2{0,0}, Vector2{0,0}, nullptr, 0, 0, 0, Vector2{0,0} }
{
}

Bullet::Bullet(const Vector2& position, const Vector2& size, Texture2D* tex, int row, int col, float speed, Vector2 direction)
	: Entity{ position, size, tex, row, col, speed, direction}
{
}