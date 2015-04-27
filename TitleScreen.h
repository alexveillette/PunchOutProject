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
class TitleScreen :
	public Sprite
{
public:
	TitleScreen();
	TitleScreen(int x, int y);
	~TitleScreen();

	void Start();
	void Update();
	void Stop();

private:
	float currentX, currentY;
	float currentTime;

	static const float SPEED;
};
