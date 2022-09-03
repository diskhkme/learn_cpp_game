#include "Player.h"

// Player 클래스의 구현

Player::Player(const Vector2& position, const Vector2& size, const Color& color, float speed)
	: position{ position }, size{ size }, color{ color }, speed{ speed }, bulletCount{ 0 }
{}

void Player::Update(float tick) 
{
	// Update 로직을 약간 수정해서, 적절한 입력이 들어올 경우 Move 그리고 Shoot을 하도록 합시다.
	// 이렇게 수정하는 이유는 입력(키보드 & 마우스)을 한 곳에서 처리하도록 하기 위함입니다.
	Vector2 moveInput = Vector2{ 0,0 };
	if (IsKeyDown(KEY_D)) moveInput.x = 1.0f;
	else if (IsKeyDown(KEY_A)) moveInput.x = -1.0f;
	if (IsKeyDown(KEY_W)) moveInput.y = -1.0f;
	else if (IsKeyDown(KEY_S)) moveInput.y = 1.0f;

	Move(tick, moveInput);

	if (IsMouseButtonPressed(0)) // IsMouseButtonPressed로 mouse가 눌렸는지 아닌지를 알 수 있습니다.
	{
		Vector2 cursorPosition = GetMousePosition(); //GetMousePosition으로 커서의 위치를 얻어올 수 있습니다.
		Vector2 direction = { cursorPosition.x - position.x, cursorPosition.y - position.y }; // 커서 위치에서 플레이어 위치(position)을 빼면, 방향 벡터가 됩니다.

		Shoot(direction);
	}

	// 총알의 Update를 호출해 주어야 합니다.
	UpdateBullets(tick);
}

void Player::Draw() const 
{
	DrawRectangle(position.x, position.y, size.x, size.y, color);
	DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK); // 테두리 그리기

	// 총알의 Draw도 호출해 주어야 합니다.
	DrawBullets();
}

Vector2 Player::GetPosition() const
{
	return position;
}

void Player::Move(float tick, Vector2 moveInput) 
{
	position.x += moveInput.x * speed * tick;
	position.y += moveInput.y * speed * tick;
}

void Player::Shoot(Vector2 shootDirection)
{
	// Bullet 배열이 50으로 한정되어 있기 때문에, 지금은 간단히 50발이 초과되면 더이상 발사되지 못하도록 하겠습니다.
	if (bulletCount < 50)
	{
		// Bullet은 플레이어 위치에서 시작해서 direction 방향으로 날아갑니다.
		// Bullet의 크기, 색상, 속도를 여기에서 상수로 넣는것은 좋지 못하지만, 현재는 일단 이렇게 두기로 합시다.
		bullets[bulletCount] = Bullet{ position, shootDirection, Vector2{3,3}, RED, 300.0f };
		bulletCount++;
	}
}

void Player::UpdateBullets(float tick)
{
	// 이미 발사된 총알도, 계속해서 위치를 업데이트 해주어야 합니다. 
	// 위치 업데이트 자체는 이 함수에서 수행하되, Player의 기본 Update() 함수에서 이 함수를 호출해 주어야 합니다.
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
