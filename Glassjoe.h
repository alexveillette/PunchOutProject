#pragma once
//There's a billion way to handle this but with only 3 animations this works just fine for our current purpose.
//Might want to consider another way to stock animations if you end up with 6-7 animations per actors.

#include "Common.h"
#include "Animation.h"


//Press A for Idle
//Press B for Walk
//Press C for Dizzy
//Press Space to Pause/Resume

class Glassjoe :
	public Animation
{
public:
	Glassjoe();
	Glassjoe(int x, int y);
	~Glassjoe();

	bool GetProtectedState() { return isProtected; }
	void Update();

	void GetsPunchedLow();
	void GetsPunchedHighLeft();
	void GetsPunchedHighRight();

private:

	float currentX;
	float currentY;

	bool isProtected;

	//States used to determine which animation will take place 
	enum state { IDLE, HOOKPUNCH, JABPUNCH, GETSPUNCHED_LOW, GETSPUNCHED_HIGHLEFT, GETSPUNCHED_HIGHRIGHT, BLOCK_LOW, BLOCK_HIGH, FLYING, KNOCKED_DOWN };
	state currentState;

	//State Setter
	void changeState(state newState);

	//This part is ugly, but at least we can use those "fake consts" in our constructor...
	const int IDLE_NB_FRAME() { return 4; }
	const int HOOKPUNCH_NB_FRAME() { return 1; }
	const int JABPUNCH_NB_FRAME() { return 1; }
	const int GETSPUNCHED_LOW_NB_FRAME() { return 1; }
	const int GETSPUNCHED_HIGHLEFT_NB_FRAME() { return 1; }
	const int GETSPUNCHED_HIGHRIGHT_NB_FRAME() { return 1; }
	const int BLOCK_LOW_NB_FRAME() { return 1; }
	const int BLOCK_HIGH_NB_FRAME() { return 1; }
	const int FLYING_NB_FRAME() { return 1; }
	const int KNOCKED_DOWN_NB_FRAME() { return 1; }
	const point<int> FRAME_SIZE() { return{ 40, 110 }; };
	const point<int> IDLE_START_SRC() { return{ 280, 220 }; };
	const point<int> HOOKPUNCH_START_SRC() { return{ 0, 0 }; };
	const point<int> JABPUNCH_START_SRC() { return{ 0, 0 }; };
	const point<int> GETSPUNCHED_LOW_START_SRC() { return{ 520, 0 }; };
	const point<int> GETSPUNCHED_HIGHLEFT_START_SRC() { return{ 560, 0 }; };
	const point<int> GETSPUNCHED_HIGHRIGHT_START_SRC() { return{ 600, 0 }; };
	const point<int> BLOCK_LOW_START_SRC() { return{ 280, 220 }; };
	const point<int> BLOCK_HIGH_START_SRC() { return{ 280, 220 }; };
	const point<int> FLYING_START_SRC() { return{ 280, 220 }; };
	const point<int> KNOCKED_DOWN_START_SRC() { return{ 280, 220 }; };


	static const float SPEED;
};



