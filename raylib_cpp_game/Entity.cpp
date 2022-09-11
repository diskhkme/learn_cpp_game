#include "Entity.h"

#include "raymath.h"

// Texture2D를 참조자에서 포인터로 바꾼 것에 주목하십시오.
// Bullet의 경우 이러한 수정이 없으면 배열로 초기화 시키기 어려울 겁니다. (이유가 뭘까요?)
Entity::Entity(const Vector2 & position, const Vector2 & size, Texture2D* tex, int row, int col, float speed, Vector2 direction)
	: position { position }, size{ size }, tex{ tex }, speed{ speed }, direction{direction}
{
	float texXStart = col * 8.0f;
	float texYStart = row * 8.0f;

	sourceRect = Rectangle{ texXStart, texYStart, 8.0f, 8.0f };
	direction = Vector2{ 0,0 }; // (주의 사항) 쓰레기값이 들어가있으면 제대로 동작하지 않게 됩니다. (이유가 뭘까요?)
}

void Entity::Update(float tick)
{
	Move(tick);
}

void Entity::Draw() const
{
	Rectangle destRect = Rectangle{ position.x, position.y, size.x, size.y };
	Vector2 origin = Vector2{ size.x / 2.0f, size.y / 2.0f };

	DrawTexturePro(*tex, sourceRect, destRect, origin, 0.0f, WHITE);
}

void Entity::UpdateDirection(const Vector2 & dir)
{
	direction = Vector2Normalize(dir);
}

void Entity::Move(float tick)
{
	position = Vector2Add(position, Vector2Scale(direction, speed*tick));
}
