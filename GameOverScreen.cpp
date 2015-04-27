#include "GameOverScreen.h"
#include "Libraries.h"

const float GameOverScreen::SPEED = 100;

GameOverScreen::GameOverScreen()
	: Sprite(Texture::ID::GameOverImage)
	, currentX(0)
	, currentY(0)
	, currentTime(0)
{
}

GameOverScreen::GameOverScreen(int x, int y)
	: Sprite(Texture::ID::GameOverImage)
	, currentX(x)
	, currentY(y)
	, currentTime(0)
	, isArriving(false)
{
	this->SetPosition(x, y);
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::Start()
{
}

void GameOverScreen::Update()
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

void GameOverScreen::Arrives()
{
	isArriving = true;
	AudioSys->PlayMusic(Musics->Get(Music::ID::GameOverScreen));
}

void GameOverScreen::Stop()
{
}