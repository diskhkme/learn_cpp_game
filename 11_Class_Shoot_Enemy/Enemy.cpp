#include "Enemy.h"

#include "raymath.h"

Enemy::Enemy()
	: Enemy{ Vector2{0,0},0,BLACK, 100 }
{}

Enemy::Enemy(const Vector2& position, float radius, const Color& color, int maxHp)
	: position{ position }, radius{ radius }, color{ color }, maxHp{ maxHp }, currentHp{ maxHp } // 생성될때는 최대 체력으로 생성됩니다.
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

	// HP가 화면에 표시되어야 그럴듯하겠죠?
	// 박스와 테두리를 이용해 화면에 체력을 표시해줍니다.
	float hpRatio = (float)currentHp / maxHp; // 현재체력/전체제력으로 비율을 계산합니다.
	DrawRectangle(position.x - radius, position.y - radius*1.5f, (radius * 2)*hpRatio, radius / 2, RED); // 그 안에 빨간 사각형을 그려 체력을 표시해줍니다. 체력이 떨어진만큼 가로 길이를 줄여줍니다.
	DrawRectangleLines(position.x - radius, position.y - radius*1.5f, radius * 2, radius / 2, BLACK); // 테두리는 그 뒤에 그려야 제대로 표시됩니다.
	
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
		// 현재 체력을 감소시키고 true를 리턴합니다.
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