#include "Bullet.h"

#include "raymath.h"

Bullet::Bullet(const Vector2& startPosition, const Vector2& direction, float speed, float radius, const Color& color)
	: currentPosition{ startPosition }, shootDirection{ Vector2Normalize(direction) }, radius{ radius }, speed{ speed }, color{ color }
{
	// 방향 벡터는 단위 벡터(길이가 1인 벡터)로 저장할 예정입니다.
	// 입력할때 제대로 길이가 1로 넘어오는지 확실하지 않고, 실수할 수도 있으므로 초기화 시점에 길이를 1로 바꾸어 줍니다.
	// (길이가 1로 넘어왔다면, 약간의 성능적인 낭비가 있는 방법이긴 합니다.)
	// 다른 사람과 협업하고 있다면, 멤버변수의 이름을 "unitDirection" 으로 더 명확하게 해 주는것도 좋을 것입니다.aaaaaaaa
}

// 각 Bullet 객체의 생성은 Player 클래스에서 수행을 하고,
// 객체가 생성된 뒤의 Update() 및 Draw() 동작은 Bullet 클래스에서 담당합니다.
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