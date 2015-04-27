#include "VictoryScreen.h"
#include "Libraries.h"

const float VictoryScreen::SPEED = 100;

VictoryScreen::VictoryScreen()
	: Sprite(Texture::ID::VictoryImage)
	, currentX(0)
	, currentY(0)
	, currentTime(0)
{
}

VictoryScreen::VictoryScreen(int x, int y)
	: Sprite(Texture::ID::VictoryImage)
	, currentX(x)
	, currentY(y)
	, currentTime(0)
	, isArriving(false)
{
	this->SetPosition(x, y);
}

VictoryScreen::~VictoryScreen()
{
}

void VictoryScreen::Start()
{
}

void VictoryScreen::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

	if (isArriving)
	{
		if (currentY < 0)
		{
			currentY += SPEED * dt * 0.5f;
			SetPosition(currentX, currentY);
		}
		else
		{
			isArriving = false;
			SetPosition(currentX, currentY);
		}
	}
}

void VictoryScreen::Arrives()
{
	isArriving = true;
	AudioSys->PlayMusic(Musics->Get(Music::ID::VictoryScreen));
}

void VictoryScreen::Stop()
{
}