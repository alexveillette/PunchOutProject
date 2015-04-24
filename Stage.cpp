#include "Stage.h"
#include "Libraries.h"

const float Stage::SPEED = 100;

Stage::Stage()
	: Sprite(Texture::ID::Stage)
	, currentX(0)
	, currentY(0)
	, currentTime(0)
{
}

Stage::Stage(int x, int y)
	: Sprite(Texture::ID::Stage)
	, currentX(x)
	, currentY(y)
	, currentTime(0)
{
	this->SetPosition(x, y);
}

Stage::~Stage()
{
}

void Stage::Start()
{
}

void Stage::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

}

void Stage::Stop()
{
}
