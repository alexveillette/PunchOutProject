#include "LittleMacHealth.h"
#include "Libraries.h"

const float LittleMacHealth::SPEED = 100;

LittleMacHealth::LittleMacHealth()
	: Sprite(Texture::ID::HealthBar)
	, currentX(0)
	, currentY(0)
{
}

LittleMacHealth::LittleMacHealth(int x, int y)
	: Sprite(Texture::ID::HealthBar)
	, currentX(x)
	, currentY(y)
{
	this->SetPosition(x, y);
}

LittleMacHealth::~LittleMacHealth()
{
}

void LittleMacHealth::Start()
{
}

void LittleMacHealth::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

}

void LittleMacHealth::Stop()
{
}

void LittleMacHealth::losesSmallHealth()
{

}
void LittleMacHealth::losesBigHealth()
{

}