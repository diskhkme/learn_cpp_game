#pragma once

#include "raylib.h"

#include "Bullet.h"

// Player 클래스의 정의
class Player
{
public:
	Player(const Vector2& position, const Vector2& size, const Color& color, float speed);
	void Update(float tick);
	void Draw() const;
	Vector2 GetPosition() const;

private:
	void Move(float tick, Vector2 moveInput);
	void Shoot(Vector2 shootDirection); // 플레이어는 이제 마우스로 총알을 발사할 수 있습니다. 

	void UpdateBullets(float tick); // 이미 발사된 총알도 계속 업데이트 해주어야 합니다.
	void DrawBullets() const; // 이미 발사된 총알도 계속 그려주어야 합니다.

private:
	Vector2 position;
	Vector2 size;
	Color color;
	float speed;

	Bullet bullets[50]; // (우선은) 발사된 총알은 Player 멤버 변수로 두고 관리합니다.
	int bulletCount; // 발사된 총알의 개수
};