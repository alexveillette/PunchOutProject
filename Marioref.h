#pragma once
//There's a billion way to handle this but with only 3 animations this works just fine for our current purpose.
//Might want to consider another way to stock animations if you end up with 6-7 animations per actors.

#include "Common.h"
#include "Animation.h"


//Press A for Idle
//Press B for Walk
//Press C for Dizzy
//Press Space to Pause/Resume

class MarioRef :
	public Animation
{
public:
	MarioRef();
	MarioRef(int x, int y);
	~MarioRef();


	void Update();
	void FightAndLeaves();
	void ComesToCount(int countNumber);
	void ChangeCount();
	void RefVictory();

private:

	float currentX;
	float currentY;
	double animationDelay;

	bool fightAndLeaves;
	bool movesIn;
	bool movesBack;
	bool isCounting;
	bool isWaiting;

	double numberToCount;
	double numberCounted;

	bool victoryKO;


	//States used to determine which animation will take place 
	enum state { IDLE, WALKING, FIGHT, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, KOSTANCE };
	state currentState;

	//State Setter
	void changeState(state newState);

	const int IDLE_NB_FRAME() { return 1; }
	const int WALKING_NB_FRAME() { return 2; }
	const int FIGHT_NB_FRAME() { return 1; }
	const int ONE_NB_FRAME() { return 1; }
	const int TWO_NB_FRAME() { return 1; }
	const int THREE_NB_FRAME() { return 1; }
	const int FOUR_NB_FRAME() { return 1; }
	const int FIVE_NB_FRAME() { return 1; }
	const int SIX_NB_FRAME() { return 1; }
	const int SEVEN_NB_FRAME() { return 1; }
	const int EIGHT_NB_FRAME() { return 1; }
	const int NINE_NB_FRAME() { return 1; }
	const int TEN_NB_FRAME() { return 1; }
	const int KOSTANCE_NB_FRAME() { return 1; }

	const point<int> FRAME_SIZE() { return{ 80, 110 }; };
	const point<int> IDLE_START_SRC() { return{ 160, 0 }; };
	const point<int> WALKING_START_SRC() { return{ 0, 0 }; };
	const point<int> FIGHT_START_SRC() { return{ 400, 110 }; };
	const point<int> ONE_START_SRC() { return{ 240, 0 }; };
	const point<int> TWO_START_SRC() { return{ 320, 0 }; };
	const point<int> THREE_START_SRC() { return{ 400, 0 }; };
	const point<int> FOUR_START_SRC() { return{ 480, 0 }; };
	const point<int> FIVE_START_SRC() { return{ 560, 0 }; };
	const point<int> SIX_START_SRC() { return{ 640, 0 }; };
	const point<int> SEVEN_START_SRC() { return{ 720, 0 }; };
	const point<int> EIGHT_START_SRC() { return{ 800, 0 }; };
	const point<int> NINE_START_SRC() { return{ 880, 0 }; };
	const point<int> TEN_START_SRC() { return{ 960, 0 }; };
	const point<int> KOSTANCE_START_SRC() { return{ 480, 110 }; };

	static const float SPEED;
};



