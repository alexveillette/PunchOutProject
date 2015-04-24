#include "GlassJoeHealth.h"
#include "Libraries.h"

const float GlassJoeHealth::SPEED = 100;

GlassJoeHealth::GlassJoeHealth()
	: Sprite(Texture::ID::HealthBar)
	, currentX(0)
	, currentY(0)
{
}

GlassJoeHealth::GlassJoeHealth(int x, int y)
	: Sprite(Texture::ID::HealthBar)
	, currentX(x)
	, currentY(y)
{
	this->SetPosition(x, y);
}

GlassJoeHealth::~GlassJoeHealth()
{
}

void GlassJoeHealth::Start()
{
}

void GlassJoeHealth::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

}

void GlassJoeHealth::Stop()
{
}