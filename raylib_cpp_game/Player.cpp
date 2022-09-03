#include "Player.h"

// Player 클래스의 구현

Player::Player(const Vector2& position, const Vector2& size, const Color& color, float speed)
	: position{ position }, size{ size }, color{ color }, speed{ speed }
{}

void Player::Update(float tick) 
{
	Move(tick);
}

void Player::Draw() const 
{
	DrawRectangle(position.x, position.y, size.x, size.y, color);
	DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK); // 테두리 그리기
}

Vector2 Player::GetPosition() const
{
	return position;
}

void Player::Move(float tick) 
{
	if (IsKeyDown(KEY_D)) position.x += speed * tick;
	else if (IsKeyDown(KEY_A)) position.x -= speed * tick;

	if (IsKeyDown(KEY_W)) position.y -= speed * tick;
	else if (IsKeyDown(KEY_S)) position.y += speed * tick;
}
