#include "GlassJoeHealth.h"
#include "Libraries.h"

const float GlassJoeHealth::SPEED = 100;

GlassJoeHealth::GlassJoeHealth()
	: Sprite(Texture::ID::HealthBar)

{
}

GlassJoeHealth::GlassJoeHealth(int x, int y)
	: Sprite(Texture::ID::HealthBar)
	, currentX(x)
	, currentY(y)
	, healthQuantity(48)
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

void GlassJoeHealth::LosesSmallHealth()
{
	healthQuantity--;
	currentX--;
	SetPosition(currentX, currentY);
}
void GlassJoeHealth::LosesBigHealth()
{

}