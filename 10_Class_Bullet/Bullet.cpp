#include "Bullet.h"

#include "raymath.h"

Bullet::Bullet(const Vector2& startPosition, const Vector2& direction, float speed, float radius, const Color& color)
	: currentPosition{ startPosition }, shootDirection{ Vector2Normalize(direction) }, radius{ radius }, speed{ speed }, color{ color }
{
	// ���� ���ʹ� ���� ����(���̰� 1�� ����)�� ������ �����Դϴ�.
	// �Է��Ҷ� ����� ���̰� 1�� �Ѿ������ Ȯ������ �ʰ�, �Ǽ��� ���� �����Ƿ� �ʱ�ȭ ������ ���̸� 1�� �ٲپ� �ݴϴ�.
	// (���̰� 1�� �Ѿ�Դٸ�, �ణ�� �������� ���� �ִ� ����̱� �մϴ�.)
	// �ٸ� ����� �����ϰ� �ִٸ�, ��������� �̸��� "unitDirection" ���� �� ��Ȯ�ϰ� �� �ִ°͵� ���� ���Դϴ�.aaaaaaaa
}

// �� Bullet ��ü�� ������ Player Ŭ�������� ������ �ϰ�,
// ��ü�� ������ ���� Update() �� Draw() ������ Bullet Ŭ�������� ����մϴ�.
void Bullet::Update()
{
	Vector2 moveDelta = Vector2Scale(shootDirection, speed);
	currentPosition = Vector2Add(currentPosition, moveDelta);
}

void Bullet::Draw() const
{
	DrawCircle(currentPosition.x, currentPosition.y, radius, color);
	DrawCircleLines(currentPosition.x, currentPosition.y, radius, BLACK);
}

Vector2 Bullet::GetPosition() const
{
	return currentPosition;
}