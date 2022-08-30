#include "Player.h"

#include "raymath.h" // Vector2XXX 연산 함수를 호출하기 위해서 필요합니다.

Player::Player(float x, float y, float width, float height, Color color)
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

	// 탄환을 발사하는 주체는 플레이어이므로, 플레이어 부분에 로직을 작성해 줍니다.
	// 또한 키보드/마우스 입력을 한 곳에서 모두 처리한다는 장점도 있습니다.

	if (IsMouseButtonPressed(0)) // IsMouseButtonDown() 함수를 통해 좌클릭(0) 또는 우클릭(1)이 발생했는지 이벤트를 얻어올 수 있습니다.
	{
		Vector2 cursorPosition = GetMousePosition(); // GetMousePosition()으로 현재 커서 위치를 얻을 수 있습니다.

		// 마우스가 클릭되었으니, 탄환을 발사해 봅시다.
		// 탄환을 메모리에 올려주고, 초기 위치와 속도 등을 설정합니다.
		// 실제 총알이 날아가는 Update()와 Draw()의 로직은 Bullet 클래스에 구현되어 있습니다.
		Vector2 shootDirection = Vector2Subtract(cursorPosition, position);
		bullets[bulletCount++] = new Bullet{ position, shootDirection, 5.0f, 3.0f, RED };
	}

	// 생성된 총알에 대해 Update를 호출하는 것도 현재는 Player의 역할입니다.
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i]->Update();
	}
}

void Player::Draw() const 
{
	DrawRectangle(position.x, position.y, size.x, size.y, color);
	DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK);

	// 생성된 총알에 대해 Draw를 호출하는 것도 현재는 Player의 역할입니다.
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i]->Draw();
	}
}

Vector2 Player::GetPosition() const
{
	return position;
}