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
	// ���� UpdateEnemy������ �ٸ� Enemy�� ��ġ�� �����Ͽ� �浹�ϴ� ��� �ڽ��� ��ġ�� �����߽��ϴ�.
	// ������ ���⼭�� �켱 �÷��̾ ���󰡴� �⺻ ��ġ �̵� ������ �������� �����,
	// �浹 ������ �κ��� ������ Main.cpp ���� UpdateEnemy�� ó���ϵ��� �߽��ϴ�.
	// ���� �߰������� ������ �ٲٴ� ���� �� ���ڽ��ϴ�.

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
