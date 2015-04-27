#pragma once

#include "Common.h"
#include "Component.h"
#include "Text.h"

class Points :
	public Text
{
public:
	Points();
	~Points();

	void Start();
	void Update();
	void Stop();
	void PunchPoints();

private:
	int pointQuantity;

};