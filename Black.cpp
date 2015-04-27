#include "Black.h"
#include "Libraries.h"

const float Black::SPEED = 100;

Black::Black()
	: Sprite(Texture::ID::BlackBackground)
	, currentX(0)
	, currentY(0)
	, currentTime(0)
{
}

Black::Black(int x, int y)
	: Sprite(Texture::ID::BlackBackground)
	, currentX(x)
	, currentY(y)
	, currentTime(0)
{
	this->SetPosition(x, y);
}

Black::~Black()
{
}

void Black::Start()
{
}

void Black::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

}

void Black::Stop()
{
}