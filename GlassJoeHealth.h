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
class GlassJoeHealth :
	public Sprite
{
public:
	GlassJoeHealth();
	GlassJoeHealth(int x, int y);
	~GlassJoeHealth();

	void Start();
	void Update();
	void Stop();

private:
	float currentX, currentY;

	static const float SPEED;
};

