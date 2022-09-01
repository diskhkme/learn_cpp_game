#include "Player.h"

#include "raymath.h" // Vector2XXX 연산 함수를 호출하기 위해서 필요합니다.

Player::Player(float x, float y, float width, float height, const Color& color)
	: position{ Vector2{x,y} }, size{ Vector2{width,height} }, color{ color }, bulletCount{ 0 }
{}

Player::~Player()
{
	for (int i = 0; i < bulletCount; i++)
	{
		delete bullets[i];
	}
}

void Player::Update() 
{
	if (IsKeyDown(KEY_D)) position.x += 2;
	else if (IsKeyDown(KEY_A)) position.x -= 2;

	if (IsKeyDown(KEY_W)) position.y -= 2;
	else if (IsKeyDown(KEY_S)) position.y += 2;

	if (IsMouseButtonPressed(0)) 
	{
		Vector2 cursorPosition = GetMousePosition(); 

		Vector2 shootDirection = Vector2Subtract(cursorPosition, position);
		bullets[bulletCount++] = new Bullet{ position, shootDirection, 10.0f, 50, 3.0f, RED };
	}

	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i]->Update();
	}
}

void Player::Draw() const 
{
	DrawRectangle(position.x, position.y, size.x, size.y, color);
	DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK);

	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i]->Draw();
	}
}

void Player::DestroyBullet(int index)
{
	// index번째 bullet을 삭제하고, 마지막 bullet을 그 자리에 바꿔서 채워넣습니다.
	if(index != bulletCount-1)
		bullets[index] = bullets[bulletCount - 1];

	bullets[bulletCount - 1] = nullptr;
	bulletCount--;
}

Vector2 Player::GetPosition() const
{
	return position;
}

int Player::GetBulletCount() const
{
	return bulletCount;
}

Bullet* Player::GetBullet(int index) const
{
	return bullets[index];
}