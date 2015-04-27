#pragma once
//There's a billion way to handle this but with only 3 animations this works just fine for our current purpose.
//Might want to consider another way to stock animations if you end up with 6-7 animations per actors.

#include "Common.h"
#include "Animation.h"
#include "GlassJoeBody.h"

//Press A for Idle
//Press B for Walk
//Press C for Dizzy
//Press Space to Pause/Resume

class Glassjoe :
	public Animation
{
public:
	Glassjoe();
	Glassjoe(int x, int y, GlassJoeBody* gjb);
	~Glassjoe();

	bool GetProtectedStateLow() { return isProtectedLow; }
	bool GetProtectedStateHigh() { return isProtectedHigh; }
	bool GetInvincibleState() { return isInvincible; }
	bool GetHookState() { return hookLands; }
	void SetHookState(bool hooking) { hookLands = hooking; }
	bool GetJabState() { return jabLands; }
	void SetJabState(bool jabbing) { jabLands = jabbing; }

	void SetActiveState(bool active) { enabled = active; }

	void Update();

	void MakesDecision();

	void GetsPunchedLow();
	void GetsPunchedHighLeft();
	void GetsPunchedHighRight();
	void SuccessfulBlockLow();
	void SuccessfulBlockHigh();
	void GetsToCenterOfRing();
	void GetsKnockedDown(int countNumber);
	void FinalKnockdown();
	void Victory();

private:

	GlassJoeBody* gjb;

	float currentX;
	float currentY;

	bool isProtectedLow;
	bool isProtectedHigh;
	bool dizzy;
	bool enabled;
	bool getsToCenterOfRing;
	bool getsKnockedDown;
	bool isDown;
	bool getsBackUp;
	bool isUp;
	double numberToCount;
	bool finalKO;

	bool isPunchingHook;
	bool isPunchingJab;
	bool hookLands;
	bool jabLands;
	bool isInvincible;

	double animationDelay;

	double decisionTimer;

	//States used to determine which animation will take place 
	enum state { IDLE,IDLE_HIGH, HOOKPUNCH, JABPUNCH, GETSPUNCHED_LOW, GETSPUNCHED_HIGHLEFT, GETSPUNCHED_HIGHRIGHT, BLOCK_LOW, BLOCK_HIGH, FLYING, KNOCKED_DOWN, COCKY, WARMUP, GETSUP, DIZZY };
	state currentState;

	//State Setter
	void changeState(state newState);

	//This part is ugly, but at least we can use those "fake consts" in our constructor...
	const int IDLE_NB_FRAME() { return 4; }
	const int IDLE_HIGH_NB_FRAME() { return 4; }
	const int HOOKPUNCH_NB_FRAME() { return 7; }
	const int JABPUNCH_NB_FRAME() { return 6; }
	const int GETSPUNCHED_LOW_NB_FRAME() { return 1; }
	const int GETSPUNCHED_HIGHLEFT_NB_FRAME() { return 1; }
	const int GETSPUNCHED_HIGHRIGHT_NB_FRAME() { return 1; }
	const int BLOCK_LOW_NB_FRAME() { return 1; }
	const int BLOCK_HIGH_NB_FRAME() { return 1; }
	const int FLYING_NB_FRAME() { return 1; }
	const int KNOCKED_DOWN_NB_FRAME() { return 1; }
	const int COCKY_NB_FRAME() { return 1; }
	const int WARMUP_NB_FRAME() { return 3; }
	const int GETSUP_NB_FRAME() { return 1; }
	const int DIZZY_NB_FRAME() { return 1; }
	const point<int> FRAME_SIZE() { return{ 40, 110 }; };
	const point<int> IDLE_START_SRC() { return{ 280, 220 }; };
	const point<int> IDLE_HIGH_START_SRC() { return{ 440, 220 }; };
	const point<int> HOOKPUNCH_START_SRC() { return{ 40, 110 }; };
	const point<int> JABPUNCH_START_SRC() { return{ 320, 110 }; };
	const point<int> GETSPUNCHED_LOW_START_SRC() { return{ 520, 0 }; };
	const point<int> GETSPUNCHED_HIGHLEFT_START_SRC() { return{ 560, 0 }; };
	const point<int> GETSPUNCHED_HIGHRIGHT_START_SRC() { return{ 600, 0 }; };
	const point<int> BLOCK_LOW_START_SRC() { return{ 160, 0 }; };
	const point<int> BLOCK_HIGH_START_SRC() { return{ 360, 0 }; };
	const point<int> FLYING_START_SRC() { return{ 0, 220 }; };
	const point<int> KNOCKED_DOWN_START_SRC() { return{ 80, 220 }; };
	const point<int> COCKY_START_SRC() { return{ 0, 0 }; };
	const point<int> WARMUP_START_SRC() { return{ 40, 0 }; };
	const point<int> GETSUP_START_SRC() { return{ 240, 220 }; };
	const point<int> DIZZY_START_SRC() { return{ 0, 110 }; };


	static const float SPEED;
};



