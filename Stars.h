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

private:
	int starQuantity;

};