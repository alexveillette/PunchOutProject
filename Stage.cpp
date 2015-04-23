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

	//if (Engine::GetInstance()->GetInput()->IsKeyHeld(SDL_SCANCODE_UP))
	//{
	//	currentY -= SPEED * dt;
	//	SetPosition((int)currentX, (int)currentY);
	//}
	//if (Engine::GetInstance()->GetInput()->IsKeyHeld(SDL_SCANCODE_DOWN))
	//{
	//	currentY += SPEED * dt;
	//	SetPosition((int)currentX, (int)currentY);
	//}
	//if (Engine::GetInstance()->GetInput()->IsKeyHeld(SDL_SCANCODE_LEFT))
	//{
	//	currentX -= SPEED * dt;
	//	SetPosition((int)currentX, (int)currentY);
	//}
	//if (Engine::GetInstance()->GetInput()->IsKeyHeld(SDL_SCANCODE_RIGHT))
	//{
	//	currentX += SPEED * dt;
	//	SetPosition((int)currentX, (int)currentY);
	//}
	//if (Engine::GetInstance()->GetInput()->IsKeyHeld(SDL_SCANCODE_END))
	//{
	//	Flip(SDL_FLIP_NONE);
	//}
	//if (Engine::GetInstance()->GetInput()->IsKeyHeld(SDL_SCANCODE_HOME))
	//{
	//	Flip(SDL_FLIP_VERTICAL);
	//}
	//if (Engine::GetInstance()->GetInput()->IsKeyHeld(SDL_SCANCODE_PAGEUP))
	//{
	//	Flip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	//}
	//if (Engine::GetInstance()->GetInput()->IsKeyHeld(SDL_SCANCODE_PAGEDOWN))
	//{
	//	Flip(SDL_FLIP_HORIZONTAL);
	//}
}

void Stage::Stop()
{
}
