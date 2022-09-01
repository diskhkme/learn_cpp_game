#pragma once

#include "raylib.h"

class Player
{
private:
	Vector2 position;
	Vector2 size;
	Color color;

public:
	Player(float x, float y, float width, float height, const Color& color);

	void Update();
	void Draw() const;
	Vector2 GetPosition() const;
};
