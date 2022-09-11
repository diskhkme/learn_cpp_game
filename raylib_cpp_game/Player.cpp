#include "Player.h"

#include "raymath.h"

// Player 클래스의 구현

Player::Player(const Vector2& position, const Vector2& size, Texture2D* tex, int row, int col, float speed, Vector2 direction, int maxHP)
	: Actor{position, size, tex, row, col, speed, direction, maxHP }
{
	// Player의 생성은 Actor에 위임합니다.
}

void Player::Update(float tick) 
{
	Vector2 moveDirection = Vector2{ 0,0 };
	if (IsKeyDown(KEY_D)) moveDirection.x = 1.0f;
	else if (IsKeyDown(KEY_A)) moveDirection.x = -1.0f;
	if (IsKeyDown(KEY_W)) moveDirection.y = -1.0f;
	else if (IsKeyDown(KEY_S)) moveDirection.y = 1.0f;

	UpdateDirection(Vector2Normalize(moveDirection));

	// direction만 정해지면 speed에 따르는 이동은 Entity에서 처리하기 때문에 직접 할 필요가 없습니다.
	Entity::Update(tick);

	// Shoot 기능은 현재는 Player의 고유 기능입니다.
	if (IsMouseButtonPressed(0))
	{
		Shoot();
	}

	// Player가 관리하므로, bullet의 Update도 호출해 주어야 합니다.
	UpdateBullets(tick);
}

void Player::Draw() const
{
	Actor::Draw();
	DrawBullets(); // Player가 관리하므로, bullet의 Draw도 호출해 주어야 합니다.
}

Vector2 Player::GetPosition() const
{
	return position;
}

void Player::SetWeapon(const Vector2 & size, Texture2D * tex, int row, int col, float speed)
{
	bulletSize = size;
	bulletTex = tex;
	bulletRow = row;
	bulletCol = col;
	bulletSpeed = speed;
}

void Player::Shoot()
{
	Vector2 cursorPos = GetMousePosition();
	Vector2 shootDirection = Vector2Normalize(Vector2Subtract(cursorPos, position));

	if (bulletCount < 50)
	{
		bullets[bulletCount] = Bullet{ position, bulletSize, bulletTex, bulletRow, bulletCol, bulletSpeed, shootDirection };
		bulletCount++;
	}
}

void Player::UpdateBullets(float tick)
{
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i].Update(tick);
	}
}

void Player::DrawBullets() const
{
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i].Draw();
	}
}
