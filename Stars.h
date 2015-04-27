#pragma once

#include "Common.h"
#include "Component.h"
#include "Text.h"

class Stars :
	public Text
{
public:
	Stars();
	~Stars();

	void Start();
	void Update();
	void Stop();

	int GetNumberOfStars(){ return starQuantity; }
	void SetNumberOfHearts(int number){ starQuantity = number; }

private:
	int starQuantity;

};