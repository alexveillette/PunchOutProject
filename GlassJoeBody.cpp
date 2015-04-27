#include "GlassJoeBody.h"
#include "Libraries.h"

const float GlassJoeBody::SPEED = 100;

GlassJoeBody::GlassJoeBody()
	: Sprite(Texture::ID::GlassJoeBody)
	, currentX(0)
	, currentY(0)
	, currentTime(0)
{
}

GlassJoeBody::GlassJoeBody(int x, int y)
	: Sprite(Texture::ID::GlassJoeBody)
	, currentX(x)
	, currentY(y)
	, currentTime(0)
{
	this->SetPosition(x, y);
}

GlassJoeBody::~GlassJoeBody()
{
}

void GlassJoeBody::Start()
{
}

void GlassJoeBody::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

}

void GlassJoeBody::Stop()
{
}
