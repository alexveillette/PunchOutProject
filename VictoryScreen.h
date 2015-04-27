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
class VictoryScreen :
	public Sprite
{
public:
	VictoryScreen();
	VictoryScreen(int x, int y);
	~VictoryScreen();

	void Start();
	void Update();
	void Stop();
	void Arrives();

private:
	float currentX, currentY;
	float currentTime;
	bool isArriving;

	static const float SPEED;
};
