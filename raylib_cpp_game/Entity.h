#pragma once

#include "raylib.h"

// 게임 내 객체들(플레이어, 적, 총알)이 가지고 있는 공통 데이터와 기능을 가지고 Entity 클래스를 정의하였습니다.
class Entity
{
public:
	Entity();
	Entity(const Vector2& position, const Vector2& size, Texture2D* tex, int row, int col, float speed, Vector2 direction);

	virtual void Update(float tick);
	virtual void Draw() const;
	
	void UpdateDirection(const Vector2& dir); //플레이어 및 적은 계속 이동방향이 변하기 때문에 UpdateDirection을 해주어야 합니다.
											  //반면 총알은 같은 방향으로 계속 날아가는 것이 기본이므로 이 함수를 사용하지 않을 예정입니다.

protected:
	void Move(float tick);

protected:
	Vector2 position;
	Vector2 size;
	Texture2D* tex; 
	Rectangle sourceRect; 

	float speed;
	Vector2 direction; // 각각 Entity의 이동 로직을 가능한 통일하기위해 direction을 기반으로 움직이도록 할 것입니다.
};