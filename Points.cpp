#include "Points.h"
#include "Libraries.h"

std::stringstream pts;

Points::Points()
	:Text("", Font::ID::Dialog, 700)
	, pointQuantity(100)

{
	SetPosition(188, 27);
	this->Scale(0.37);
	SetText(pts.str());
}

Points::~Points()
{
}

void Points::Start()
{
}

void Points::Update()
{
	if (pointQuantity > 99 && pointQuantity < 1000)
	{
		this->SetPosition(172, 27);
	}
	pts << pointQuantity;


	SetText(pts.str());
	Text::Update();
	pts.str(std::string());
}

void Points::Stop()
{
}