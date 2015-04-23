#include "Engine.h"
#include "Sprite.h"
#include "Littlemac.h"
#include "Glassjoe.h"
#include "Stage.h"
#include "Libraries.h"
#include "Littlemac.h"
#include "Marioref.h"
#include "ResourceIDs.h"
#include "PunchOutTimer.h"
#include "Hearts.h"
#include "Stars.h"
#include "Points.h"

typedef int* pInt;

int main(int argc, char* args[])
{
	//Initializes the engine
	Engine::GetInstance()->Init(800, 750, RESOLUTION_NTSC);

	//Loading resources
	Textures->LoadTexture(Texture::ID::Littlemac, "littlemac.png");
	Textures->LoadTexture(Texture::ID::Glassjoe, "glassjoe.png");
	Textures->LoadTexture(Texture::ID::Stage, "background.png");
	Sounds->LoadSound(Sound::ID::EnemyHit, "EnemyHit.wav");
	Musics->LoadMusic(Music::ID::TestMusic, "TestMusic.mp3");
	Fonts->LoadFont(Font::ID::Dialog, "punchoutnes.ttf", 23);

	//Soundtest		demonstrates the Audio system's functionnalities,	 look at SoundTest.H for info on the various controls: ([1-6], Numpad[1-6], +, -)
	//SpriteTest	demonstrates the Sprite system's functionnalities,	 look at SpriteTest.H for info on the various controls: (Up, Down, Left, Right, PageUp, PageDown, End, Home)
	//AnimationTest demonstrates the Animation system's functionnalities,look at AnimationTest.H for info on the various controls: (A, B, C, Space)
	//TextTest		demonstrates the Text system's functionnalities,	 look at TextTest.H for info on the various controls: (F1-F7)

	Stage*		stage = new Stage(0, 0);
	Glassjoe*	glassjoe = new Glassjoe(110, 67);
	Littlemac*	littlemac = new Littlemac(100, 120, glassjoe);
	PunchOutTimer* timer = new PunchOutTimer();
	Hearts* hearts = new Hearts();
	Stars* stars = new Stars();
	Points* points = new Points();

	Engine::GetInstance()->Run();

	return 0;
}