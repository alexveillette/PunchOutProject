#pragma once
//There's a billion way to handle this but with only 3 animations this works just fine for our current purpose.
//Might want to consider another way to stock animations if you end up with 6-7 animations per actors.

#include "Common.h"
#include "Animation.h"
#include "Glassjoe.h"
#include "Hearts.h"
#include "Stars.h"
#include "Points.h"
#include "LittleMacHealth.h"
#include "GlassJoeHealth.h"


//Press A for Idle
//Press B for Walk
//Press C for Dizzy
//Press Space to Pause/Resume

class Littlemac :
	public Animation
{
public:
	Littlemac();
	Littlemac(int x, int y, Glassjoe* gj, Hearts* hearts, Stars* stars, Points* points, LittleMacHealth* lmHealth, GlassJoeHealth* gjHealth);
	~Littlemac();

	void Update();

private:

	Hearts* hearts; 
	Stars* stars; 
	Points* points; 
	LittleMacHealth* lmHealth;
	GlassJoeHealth* gjHealth;
	Glassjoe* gj;

	bool isMoving;

	double inputDelay;
	double animationDelay;

	bool isPunching;
	bool isDodging;
	bool isBlockingHigh;
	bool comingBackfromDodgeLeft;
	bool comingBackfromDodgeRight;
	bool comingBackFromPunch;
	bool comingBackFromLowPunch;
	bool upMode;
	bool dodgingLeft;
	bool dodgingRight;
	bool highPunch;
	bool lowPunch;
	bool punchConnectedLow;
	bool punchConnectedHighLeft;
	bool punchConnectedHighRight;

	Vector2D dodgeDir;
	float currentX;
	float currentY;


	//States used to determine which animation will take place 
	enum state { IDLE, LEFTDODGE, RIGHTDODGE, LEFTLOWPUNCH, LEFTHIGHPUNCH, RIGHTLOWPUNCH, RIGHTHIGHPUNCH, UPPERCUT, HIGHBLOCK, DUCK };
	state currentState;

	//State Setter
	void changeState(state newState);

	//This part is ugly, but at least we can use those "fake consts" in our constructor...
	const int IDLE_NB_FRAME() { return 2; }
	const int WALK_NB_FRAME() { return 6; }
	const int DIZZY_NB_FRAME() { return 2; }
	const int LEFTDODGE_NB_FRAME() { return 1; }
	const int RIGHTDODGE_NB_FRAME() { return 1; }
	const int LEFTLOWPUNCH_NB_FRAME() { return 4; }
	const int LEFTHIGHPUNCH_NB_FRAME() { return 4; }
	const int RIGHTLOWPUNCH_NB_FRAME() { return 4; }
	const int RIGHTHIGHPUNCH_NB_FRAME() { return 4; }
	const int UPPERCUT_NB_FRAME() { return 5; }
	const int HIGHBLOCK_NB_FRAME() { return 1; }
	const int DUCK_NB_FRAME() { return 1; }
	const point<int> FRAME_SIZE() { return{ 40, 81 }; };
	const point<int> IDLE_START_SRC() { return{ 0, 0 }; };
	const point<int> LEFTDODGE_START_SRC() { return{ 120, 0 }; };
	const point<int> RIGHTDODGE_START_SRC() { return{ 200, 0 }; };
	const point<int> LEFTLOWPUNCH_START_SRC() { return{ 400, 0 }; };
	const point<int> LEFTHIGHPUNCH_START_SRC() { return{ 480, 118 }; };
	const point<int> RIGHTLOWPUNCH_START_SRC() { return{ 0, 118 }; };
	const point<int> RIGHTHIGHPUNCH_START_SRC() { return{ 120, 118 }; };
	const point<int> UPPERCUT_START_SRC() { return{ 0, 0 }; };
	const point<int> HIGHBLOCK_START_SRC() { return{ 320, 0 }; };
	const point<int> DUCK_START_SRC() { return{ 0, 0 }; };


	static const float SPEED;
	static const int LEFT_SIDE_PUNCH;
	static const int RIGHT_SIDE_PUNCH;
};