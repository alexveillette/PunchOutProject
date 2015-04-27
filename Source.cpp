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
#include "Libraries.h"
#include "TitleScreen.h"
#include "VictoryScreen.h"
#include "GameOverScreen.h"
#include "GlassJoeBody.h"
#include "Black.h"
#include <time.h>


typedef int* pInt;

int main(int argc, char* args[])
{
	//Initializes the engine
	Engine::GetInstance()->Init(800, 750, RESOLUTION_NTSC);

	srand((time(0)));

	//Loading resources
	Textures->LoadTexture(Texture::ID::Littlemac, "littlemac.png");
	Textures->LoadTexture(Texture::ID::Glassjoe, "glassjoe.png");
	Textures->LoadTexture(Texture::ID::Stage, "background.png");
	Textures->LoadTexture(Texture::ID::HealthBar, "healthbar.png");
	Textures->LoadTexture(Texture::ID::TitleScreen, "introscreen.png");
	Textures->LoadTexture(Texture::ID::VictoryImage, "victoryimage.png");
	Textures->LoadTexture(Texture::ID::GameOverImage, "gameoverimage.png");
	Textures->LoadTexture(Texture::ID::MarioRef, "marioref.png");
	Textures->LoadTexture(Texture::ID::GlassJoeBody, "gjbody.png");
	Textures->LoadTexture(Texture::ID::BlackBackground, "blackbackground.png");
	Sounds->LoadSound(Sound::ID::EnemyHit, "EnemyHit.wav");
	Musics->LoadMusic(Music::ID::PunchOutMusic, "bouttheme.mp3");
	Musics->LoadMusic(Music::ID::GlassJoeIntro, "glassjoeintro.mp3");
	Musics->LoadMusic(Music::ID::GlassJoeKO, "glassjoeko.mp3");
	Musics->LoadMusic(Music::ID::TitleScreen, "titletheme.mp3");
	Musics->LoadMusic(Music::ID::VictoryScreen, "victorytheme.mp3");
	Musics->LoadMusic(Music::ID::GameOverScreen, "gameovertheme.mp3");
	Musics->LoadMusic(Music::ID::LittleMacKO, "littlemacko.mp3");


	Fonts->LoadFont(Font::ID::Dialog, "punchoutnes.ttf", 23);


	AudioSys->PlayMusic(Musics->Get(Music::ID::TitleScreen));
	GlassJoeHealth* glassJoeHealth = new GlassJoeHealth(146, 18);
	Black* bbg = new Black(-120, 0);
	LittleMacHealth* littleMacHealth = new LittleMacHealth(90, 18);

	Stage*	stage = new Stage(0, 0);
	Hearts* hearts = new Hearts();
	Stars* stars = new Stars();
	Points* points = new Points();
	GlassJoeBody* gjb = new GlassJoeBody(-100, -100);
	Glassjoe*	gj = new Glassjoe(180, 30, gjb);
	MarioRef* mr = new MarioRef(130, 65);
	PunchOutTimer* timer = new PunchOutTimer();

	TitleScreen* ts = new TitleScreen();
	GameOverScreen* goScreen = new GameOverScreen(0, -300);
	VictoryScreen* viScreen = new VictoryScreen(0, -300);

	Littlemac*	lm = new Littlemac(100, 120, gj, hearts, stars, points, littleMacHealth, glassJoeHealth, ts, mr, timer, goScreen, viScreen);



	Engine::GetInstance()->Run();

	delete stage;
	delete hearts;
	delete glassJoeHealth;
	delete littleMacHealth;
	delete stars;
	delete points;
	delete gjb;
	delete gj;
	delete mr;
	delete timer;
	delete goScreen;
	delete viScreen;
	delete ts;
	delete lm;


	return 0;
}