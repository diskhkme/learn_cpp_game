#pragma once

#include "raylib.h"

#include "Bullet.h"

class Player
{
private:
	Vector2 position;
	Vector2 size;
	Color color;

	Bullet* bullets[50]; 
	int bulletCount;
public:
	Player(float x, float y, float width, float height, const Color& color);
	~Player(); 

	void Update();
	void Draw() const;
	void DestroyBullet(int index);

	Vector2 GetPosition() const;
	int GetBulletCount() const;
	Bullet* GetBullet(int index) const;
};
