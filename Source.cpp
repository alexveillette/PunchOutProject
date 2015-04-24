#include "Engine.h"
#include "Sprite.h"
#include "Stage.h"
#include "Libraries.h"
#include "Littlemac.h"
#include "Marioref.h"
#include "ResourceIDs.h"
#include "PunchOutTimer.h"
#include "Hearts.h"
#include "Stars.h"
#include "Points.h"
#include "Littlemac.h"
#include "Glassjoe.h"
#include "LittleMacHealth.h"
#include "GlassJoeHealth.h"

typedef int* pInt;

int main(int argc, char* args[])
{
	//Initializes the engine
	Engine::GetInstance()->Init(800, 750, RESOLUTION_NTSC);

	//Loading resources
	Textures->LoadTexture(Texture::ID::Littlemac, "littlemac.png");
	Textures->LoadTexture(Texture::ID::Glassjoe, "glassjoe.png");
	Textures->LoadTexture(Texture::ID::Stage, "background.png");
	Textures->LoadTexture(Texture::ID::HealthBar, "healthbar.png");
	Sounds->LoadSound(Sound::ID::EnemyHit, "EnemyHit.wav");
	Musics->LoadMusic(Music::ID::PunchOutMusic, "bouttheme.mp3");
	Musics->LoadMusic(Music::ID::GlassJoeIntro, "glassjoeintro.mp3");
	Musics->LoadMusic(Music::ID::GlassJoeKO, "glassjoeko.mp3");

	Fonts->LoadFont(Font::ID::Dialog, "punchoutnes.ttf", 23);

	//Soundtest		demonstrates the Audio system's functionnalities,	 look at SoundTest.H for info on the various controls: ([1-6], Numpad[1-6], +, -)
	//SpriteTest	demonstrates the Sprite system's functionnalities,	 look at SpriteTest.H for info on the various controls: (Up, Down, Left, Right, PageUp, PageDown, End, Home)
	//AnimationTest demonstrates the Animation system's functionnalities,look at AnimationTest.H for info on the various controls: (A, B, C, Space)
	//TextTest		demonstrates the Text system's functionnalities,	 look at TextTest.H for info on the various controls: (F1-F7)

	//HEALTH IS 48 PIXELS
	AudioSys->PlayMusic(Musics->Get(Music::ID::PunchOutMusic));
	LittleMacHealth* littleMacHealth = new LittleMacHealth(90, 18);
	GlassJoeHealth* glassJoeHealth = new GlassJoeHealth(146, 18);
	Stage*		stage = new Stage(0, 0);
	Hearts* hearts = new Hearts();
	Stars* stars = new Stars();
	Points* points = new Points();
	Glassjoe*	gj = new Glassjoe(110, 67);
	Littlemac*	lm = new Littlemac(100, 120, gj, hearts, stars, points, littleMacHealth, glassJoeHealth);

	PunchOutTimer* timer = new PunchOutTimer();


	Engine::GetInstance()->Run();

	return 0;
}