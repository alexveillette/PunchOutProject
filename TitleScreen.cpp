#include "TitleScreen.h"
#include "Libraries.h"

const float TitleScreen::SPEED = 100;

TitleScreen::TitleScreen()
	: Sprite(Texture::ID::TitleScreen)
	, currentX(0)
	, currentY(0)
	, currentTime(0)
{
}

TitleScreen::TitleScreen(int x, int y)
	: Sprite(Texture::ID::TitleScreen)
	, currentX(x)
	, currentY(y)
	, currentTime(0)
{
	this->SetPosition(x, y);
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::Start()
{
}

void TitleScreen::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

}

void TitleScreen::Stop()
{
}
