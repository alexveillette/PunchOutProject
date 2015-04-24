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
class LittleMacHealth :
	public Sprite
{
public:
	LittleMacHealth();
	LittleMacHealth(int x, int y);
	~LittleMacHealth();

	void Start();
	void Update();
	void Stop();

	float GetCurrentX(){ return currentX; }
	float GetCurrentY(){ return currentY; }

	void losesSmallHealth();
	void losesBigHealth();

private:
	float currentX, currentY;

	static const float SPEED;
};

