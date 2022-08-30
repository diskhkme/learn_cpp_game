#include "Player.h"

#include "raymath.h" // Vector2XXX ���� �Լ��� ȣ���ϱ� ���ؼ� �ʿ��մϴ�.

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

	// źȯ�� �߻��ϴ� ��ü�� �÷��̾��̹Ƿ�, �÷��̾� �κп� ������ �ۼ��� �ݴϴ�.
	// ���� Ű����/���콺 �Է��� �� ������ ��� ó���Ѵٴ� ������ �ֽ��ϴ�.

	if (IsMouseButtonPressed(0)) // IsMouseButtonDown() �Լ��� ���� ��Ŭ��(0) �Ǵ� ��Ŭ��(1)�� �߻��ߴ��� �̺�Ʈ�� ���� �� �ֽ��ϴ�.
	{
		Vector2 cursorPosition = GetMousePosition(); // GetMousePosition()���� ���� Ŀ�� ��ġ�� ���� �� �ֽ��ϴ�.

		// ���콺�� Ŭ���Ǿ�����, źȯ�� �߻��� ���ô�.
		// źȯ�� �޸𸮿� �÷��ְ�, �ʱ� ��ġ�� �ӵ� ���� �����մϴ�.
		// ���� �Ѿ��� ���ư��� Update()�� Draw()�� ������ Bullet Ŭ������ �����Ǿ� �ֽ��ϴ�.
		Vector2 shootDirection = Vector2Subtract(cursorPosition, position);
		bullets[bulletCount++] = new Bullet{ position, shootDirection, 5.0f, 3.0f, RED };
	}

	// ������ �Ѿ˿� ���� Update�� ȣ���ϴ� �͵� ����� Player�� �����Դϴ�.
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i]->Update();
	}
}

void Player::Draw() const 
{
	DrawRectangle(position.x, position.y, size.x, size.y, color);
	DrawRectangleLines(position.x, position.y, size.x, size.y, BLACK);

	// ������ �Ѿ˿� ���� Draw�� ȣ���ϴ� �͵� ����� Player�� �����Դϴ�.
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i]->Draw();
	}
}

Vector2 Player::GetPosition() const
{
	return position;
}