#pragma once

#include "Common.h"
#include "Sprite.h"

//Up		- Move Up
//Down		- Move Down
//Left		- Move Left
//Right		- Move Right
//End		- No Flip
//Home		- Flip Vertical
//PageUp	- Flip Horizontal && Vertical
//PageDown  - Flip Horizontal
class Black :
	public Sprite
{
public:
	Black();
	Black(int x, int y);
	~Black();

	void Start();
	void Update();
	void Stop();

private:
	float currentX, currentY;
	float currentTime;

	static const float SPEED;
};
