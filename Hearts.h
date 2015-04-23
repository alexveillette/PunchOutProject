#pragma once

#include "Common.h"
#include "Component.h"
#include "Text.h"

class Hearts :
	public Text
{
public:
	Hearts();
	~Hearts();

	void Start();
	void Update();
	void Stop();

private:
	int heartQuantity;

};