#include "Player.h"

Player::Player(float x, float y, float width, float height, Color color)
	: position{ Vector2{x,y} }, size{ Vector2{width,height} }, color{ color }
{}

void Player::Update() 
{
	if (IsKeyDown(KEY_D)) position.x += 2;
	else if (IsKeyDown(KEY_A)) position.x -= 2;

	if (IsKeyDown(KEY_W)) position.y -= 2;
	else if (IsKeyDown(KEY_S)) position.y += 2;
}

void Player::Draw() const 
{
	DrawRectangle(position.x, position.y, size.x, size.y, color);
	DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK);
}

Vector2 Player::GetPosition() const
{
	return position;
}