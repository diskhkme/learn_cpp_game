#include "Actor.h"

Actor::Actor(const Vector2 & position, const Vector2 & size, Texture2D * tex, int row, int col, float speed, Vector2 direction, int maxHP)
	: Entity{ position, size, tex, row, col, speed, direction }, maxHP{ maxHP }, currentHP{ maxHP }
{
}

void Actor::Draw() const
{
	Entity::Draw(); // 먼저 Entity의 Draw로 화면에 나타내는 기본 요소를 그립니다.

	DrawHpBar(); // 이후 HP 바를 그립니다.
}

void Actor::DrawHpBar() const
{
	float fullHpBoxWidth = size.x * 1.2f;
	float hpBoxHeight = size.y * 0.2f;

	float xAnchor = position.x - fullHpBoxWidth / 2.0f;
	float yAnchor = position.y - size.y * 0.8f;
	
	DrawRectangle(xAnchor, yAnchor, fullHpBoxWidth, hpBoxHeight, RED);

	float redHpBoxWidth = fullHpBoxWidth * ((float)currentHP / maxHP);
	DrawRectangle(xAnchor, yAnchor, redHpBoxWidth, hpBoxHeight, GREEN);
}
