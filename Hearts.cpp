#include "Hearts.h"
#include "Libraries.h"

std::stringstream hs;

Hearts::Hearts()
	:Text("", Font::ID::Dialog, 700)
	, heartQuantity(20)

{
	SetPosition(57, 18);
	this->Scale(0.4);
	this->SetColor(Color::YELLOW);
	SetText(hs.str());
}

Hearts::~Hearts()
{
}

void Hearts::Start()
{
}

void Hearts::Update()
{
	if (heartQuantity < 10)
	{
		SetPosition(66, 18);
	}
	if (heartQuantity < 0)
	{
		heartQuantity = 0;
	}

	hs << heartQuantity;

	SetText(hs.str());
	Text::Update();
	hs.str(std::string());
}

void Hearts::LosesHeart()
{
	heartQuantity--;
}
void Hearts::Stop()
{
}