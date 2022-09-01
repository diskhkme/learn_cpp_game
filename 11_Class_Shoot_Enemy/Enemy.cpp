#include "Enemy.h"

#include "raymath.h"

Enemy::Enemy()
	: Enemy{ Vector2{0,0},0,BLACK, 100 }
{}

Enemy::Enemy(const Vector2& position, float radius, const Color& color, int maxHp)
	: position{ position }, radius{ radius }, color{ color }, maxHp{ maxHp }, currentHp{ maxHp } // �����ɶ��� �ִ� ü������ �����˴ϴ�.
{}

void Enemy::Update(const Vector2& playerPosition)
{
	Vector2 enemyToPlayerVector = Vector2Subtract(playerPosition, position);
	Vector2 enemyToPlayerDirection = Vector2Normalize(enemyToPlayerVector);

	position.x += enemyToPlayerDirection.x;
	position.y += enemyToPlayerDirection.y;
}

void Enemy::Draw() const
{
	DrawCircle(position.x, position.y, radius, color);
	DrawCircleLines(position.x, position.y, radius, BLACK);

	// HP�� ȭ�鿡 ǥ�õǾ�� �׷����ϰ���?
	// �ڽ��� �׵θ��� �̿��� ȭ�鿡 ü���� ǥ�����ݴϴ�.
	float hpRatio = (float)currentHp / maxHp; // ����ü��/��ü�������� ������ ����մϴ�.
	DrawRectangle(position.x - radius, position.y - radius*1.5f, (radius * 2)*hpRatio, radius / 2, RED); // �� �ȿ� ���� �簢���� �׷� ü���� ǥ�����ݴϴ�. ü���� ��������ŭ ���� ���̸� �ٿ��ݴϴ�.
	DrawRectangleLines(position.x - radius, position.y - radius*1.5f, radius * 2, radius / 2, BLACK); // �׵θ��� �� �ڿ� �׷��� ����� ǥ�õ˴ϴ�.
	
}

bool Enemy::CheckCollision(const Enemy& other)
{
	if (CheckCollisionCircles(position, radius, other.position, other.radius))
	{
		return true;
	}

	return false;
}

bool Enemy::CheckHit(const Bullet& other)
{
	if (CheckCollisionCircles(position, radius, other.GetPosition(), other.GetRadius()))
	{
		// ���� ü���� ���ҽ�Ű�� true�� �����մϴ�.
		currentHp -= other.GetDamage();
		return true;
	}

	return false;
}

Vector2 Enemy::GetPosition() const
{
	return position;
}

void Enemy::SetPosition(const Vector2& pos)
{
	position = pos;
}

float Enemy::GetRadius() const
{
	return radius;
}

int Enemy::GetCurrentHp() const
{
	return currentHp;
}