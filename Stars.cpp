#include "Stars.h"
#include "Libraries.h"

std::stringstream strs;

Stars::Stars()
	:Text("", Font::ID::Dialog, 700)
	, starQuantity(0)

{
	SetPosition(33, 18);
	this->Scale(0.4);
	this->SetColor(Color::YELLOW);
	SetText(strs.str());
}

Stars::~Stars()
{
}

void Stars::Start()
{
}

void Stars::Update()
{
	if (starQuantity >= 4)
	{
		starQuantity = 3;
	}

	strs << starQuantity;

	
	SetText(strs.str());
	Text::Update();
	strs.str(std::string());
}

void Stars::Stop()
{
}