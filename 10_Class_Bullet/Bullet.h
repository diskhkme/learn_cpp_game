#pragma once

#include "raylib.h"

// 탄환(Bullet)은 사용자에게서 출발하여, 마우스 방향으로 날아가는 물체에 대한 정의입니다.
// 적에게 맞으면 사라지면서 적에게 데미지를 주도록 할텐데, 이번 장에서는 우선 클릭시 마우스 방향으로 날아가는 로직만 작성해 봅시다.
class Bullet
{
private:
	// 멤버 변수에 담고있는 값은 (계속 변화하는) 현재 위치라는 것이 명확하도록 이름을 바꾸어줍니다.
	Vector2 currentPosition;
	const Vector2 shootDirection; // 탄환의 방향은 변하지 않기 때문에 const로 지정해 줍니다.
								  // 사실 현재도 (Player, Enemy 클래스 등도 마찬가지) radius, color 등이 변하지 않지만 지금까지 const로 지정해 주진 않았습니다.
								  // 이는 추후에 이런 값들을 변경할 것을 저는 미리 고려하였기 때문입니다. 여러분은 몰랐으니^^; 이상하게 생각하셨어야 맞습니다.
	float radius;
	Color color;

	float speed;
public:
	// 초기에 생성할때는 시작 위치와 방향을 넣어줍니다.
	Bullet(Vector2 startPosition, Vector2 direction, float speed, float radius,  Color color);

	void Update();
	void Draw() const;
	Vector2 GetPosition() const;
};