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

	int GetHealthQuantity(){ return healthQuantity; }
	void SetHealthQuantity(int health){ this->healthQuantity = health; }


	void LosesSmallHealth();

private:
	float currentX, currentY;

	int healthQuantity;

	static const float SPEED;
};

