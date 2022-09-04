#include "Player.h"

#include "raymath.h"

// Player 클래스의 구현

Player::Player(const Vector2& position, const Vector2& size, const Texture2D& tex, int row, int col, float speed)
	: position{ position }, tex{ tex }, size{ size }, speed{ speed }, bulletCount{ 0 }
{
	// tex 이미지의 각 요소는 8픽셀 크기입니다. 따라서 지정한 row, col에 8을 곱해주면,
	// 내가 사용하려는 이미지의 좌상단 좌표값을 얻을 수 있습니다.
	float texXStart = col * 8.0f;
	float texYStart = row * 8.0f;

	// Rectangle 구조체는 x좌표, y좌표, 넓이, 높이 네 개의 값을 갖는 구조체입니다.
	// 내가 사용할 이미지는 texXStart, texYStart가 좌상단인 8x8 크기의 픽셀입니다.
	sourceRect = Rectangle{ texXStart, texYStart, 8.0f, 8.0f };
}

void Player::Update(float tick) 
{
	// raymath에서 제공하는 벡터 계산 기능을 사용해서 코드를 조금 더 단축시켜 봅시다.
	// raymath는 c언어 기반으로 작성되었기 때문에 약간 보기에는 불편한 면이 있기도 하지만, 필요한 계산 기능이 모두 구현되어 있으니 편합니다.

	Vector2 moveInput = Vector2{ 0,0 };
	if (IsKeyDown(KEY_D)) moveInput.x = 1.0f;
	else if (IsKeyDown(KEY_A)) moveInput.x = -1.0f;
	if (IsKeyDown(KEY_W)) moveInput.y = -1.0f;
	else if (IsKeyDown(KEY_S)) moveInput.y = 1.0f;

	Move(tick, moveInput);

	if (IsMouseButtonPressed(0)) 
	{
		Vector2 cursorPosition = GetMousePosition(); 
		Vector2 direction = Vector2Subtract(cursorPosition, position); // Vector2끼리의 뺄셈연산, Vector2Substract

		Shoot(direction);
	}

	// 총알의 Update를 호출해 주어야 합니다.
	UpdateBullets(tick);
}

void Player::Draw() const 
{
	// 화면에 이미지를 그릴 대상 위치는 position(플레이어의 위치)이 좌상단인,
	// size 크기의 사각형입니다.
	Rectangle destRect = Rectangle{ position.x, position.y, size.x, size.y };
	Vector2 origin = Vector2{ size.x / 2.0f, size.y / 2.0f };
	
	// 이제 DrawRectangle대신 DrawTextureRec를 사용해서 플레이어를 그립니다.
	// tex로부터 sourceRect만큼을 떼어와서(?) destRect로 정의된 사각형에 그립니다.
	// destRect가 더 크기 때문에 이미지 크기가 늘어가게 됩니다.
	DrawTexturePro(tex, sourceRect, destRect, origin, 0.0f, WHITE);

	// 총알의 Draw도 호출해 주어야 합니다.
	DrawBullets();
}

Vector2 Player::GetPosition() const
{
	return position;
}

void Player::Move(float tick, Vector2 moveInput) 
{
	Vector2 positionDelta = Vector2Scale(moveInput, speed*tick); // Vector의 각 요소에 상수 곱하기, Vector2Scale
	position = Vector2Add(position, positionDelta); // 두 벡터 더하기, Vector2Add
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
