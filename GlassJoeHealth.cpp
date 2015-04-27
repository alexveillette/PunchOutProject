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
	, restoringHealth(false)
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

	if (restoringHealth == true);
	{
		if (currentX < (healthQuantity + 98))
		{
			currentX += SPEED * dt * 0.3f;
			SetPosition(currentX, currentY);
		}
		else
		{
			restoringHealth = false;
		}
	}
}

void GlassJoeHealth::Stop()
{
}

void GlassJoeHealth::LosesSmallHealth()
{
	healthQuantity-= 4;
	currentX -= 4;
	SetPosition(currentX, currentY);

}
void GlassJoeHealth::LosesBigHealth()
{

}

void GlassJoeHealth::RestoreHealth()
{
	int healthToRestore = rand() % 20 + 22;
	healthQuantity += healthToRestore;
	restoringHealth = true;
}