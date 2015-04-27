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

	void LosesHeart();

	int GetNumberOfHearts(){return heartQuantity;}
	void SetNumberOfHearts(int number){ heartQuantity = number; }

private:
	int heartQuantity;

};