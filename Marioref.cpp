#include "MarioRef.h"
#include "Libraries.h"

const float MarioRef::SPEED = 100;

MarioRef::MarioRef()
	: Animation(Texture::ID::MarioRef, IDLE_NB_FRAME(), 3, IDLE_START_SRC(), FRAME_SIZE())
{
	//Start the animation on creation
	this->Play();
	//Make it loop
	this->SetIsLooping(true);
}

MarioRef::MarioRef(int x, int y)
	: Animation(Texture::ID::MarioRef, IDLE_NB_FRAME(), 4, IDLE_START_SRC(), FRAME_SIZE())
	, currentState(IDLE)
	, currentX(x)
	, currentY(y)
	, fightAndLeaves(false)
	, movesBack(false)
	, movesIn(false)
	, isCounting(false)
	, isWaiting(false)
	, animationDelay(0)
	, numberToCount(0)
	, numberCounted(0)
	, victoryKO(false)

{
	this->SetPosition(x, y);
	//Start the animation on creation
	this->Play();
	//Make it loop
	this->SetIsLooping(true);

	numberToCount = 0;
}

//Really basic animation state change
//You'd want to use another system to store an object's multiple animations
void MarioRef::changeState(state newState)
{
	if (this->currentState != newState)
	{
		switch (newState)
		{
		case IDLE:
			this->SetSrcPos(IDLE_START_SRC());
			this->SetNbFrame(IDLE_NB_FRAME());
			this->SetFrameRate(3);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case FIGHT:
			this->SetSrcPos(FIGHT_START_SRC());
			this->SetNbFrame(FIGHT_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case WALKING:
			this->SetSrcPos(WALKING_START_SRC());
			this->SetNbFrame(WALKING_NB_FRAME());
			this->SetFrameRate(20);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case ONE:
			this->SetSrcPos(ONE_START_SRC());
			this->SetNbFrame(ONE_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case TWO:
			this->SetSrcPos(TWO_START_SRC());
			this->SetNbFrame(TWO_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case THREE:
			this->SetSrcPos(THREE_START_SRC());
			this->SetNbFrame(THREE_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case FOUR:
			this->SetSrcPos(FOUR_START_SRC());
			this->SetNbFrame(FOUR_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case FIVE:
			this->SetSrcPos(FIVE_START_SRC());
			this->SetNbFrame(FIVE_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case SIX:
			this->SetSrcPos(SIX_START_SRC());
			this->SetNbFrame(SIX_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case SEVEN:
			this->SetSrcPos(SEVEN_START_SRC());
			this->SetNbFrame(SEVEN_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case EIGHT:
			this->SetSrcPos(EIGHT_START_SRC());
			this->SetNbFrame(EIGHT_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case NINE:
			this->SetSrcPos(NINE_START_SRC());
			this->SetNbFrame(NINE_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case TEN:
			this->SetSrcPos(TEN_START_SRC());
			this->SetNbFrame(TEN_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case KOSTANCE:
			this->SetSrcPos(KOSTANCE_START_SRC());
			this->SetNbFrame(KOSTANCE_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;

		default:
			break;
		}
		//It's important to reset back to the first frame on change
		this->currentState = newState;
		this->ResetCurrentFrame();
	}
}

void MarioRef::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

	Animation::Update();




	if (fightAndLeaves == true)
	{

		if (animationDelay > 0)
		{
			animationDelay -= dt;
		}

		if (animationDelay <= 0)
		{
			animationDelay = 0;
			changeState(WALKING);
			movesBack = true;
		}
	}

	if (movesBack == true)
	{
		if (currentX < 250)
		{
			currentX += SPEED * dt * 0.5;
			SetPosition(currentX, currentY);
		}
		else
		{
			movesBack = false;
			fightAndLeaves = false;
		}
	}

	if (movesIn == true)
	{
		if (animationDelay > 0)
		{
			animationDelay -= dt;
		}

		if (currentX > 130)
		{
			currentX -= SPEED * dt * 0.5;
			SetPosition(currentX, currentY);
		}
		else if (currentX <= 130 && animationDelay <= 0)
		{
			movesIn = false;
			changeState(ONE);
			animationDelay += 1.0f;
			isCounting = true;
		}
	}

	if (isCounting == true)
	{
		if (victoryKO == false)
		{
			if (animationDelay > 0)
			{
				animationDelay -= dt;
			}

			if (numberToCount > 0 && animationDelay <= 0)
			{
				ChangeCount();
			}

			else if (numberToCount == 0 && animationDelay <= 0)
			{
				changeState(IDLE);
				std::cout << "GETSUP!" << std::endl;
				animationDelay += 5.0f;
				isCounting = false;
				isWaiting = true;
			}
		}
		else if (victoryKO == true)
		{
			changeState(KOSTANCE);
		}

	}

	if (isWaiting == true)
	{
		if (animationDelay > 0)
		{
			animationDelay -= dt;
		}
		if (animationDelay <= 0)
		{
			isWaiting = false;
			FightAndLeaves();
			numberCounted = 0;
			numberToCount = 0;
		}
	}
}

void MarioRef::FightAndLeaves()
{
	changeState(FIGHT);
	animationDelay += 0.8f;
	fightAndLeaves = true;
}

void MarioRef::ComesToCount(int countNumber)
{
	numberToCount = countNumber;
	animationDelay += 2.8f;
	changeState(WALKING);
	movesIn = true;
}

void MarioRef::ChangeCount()
{
	std::cout << "CHANGECOUNT!" << std::endl;
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();
	numberToCount --;
	numberCounted ++;
	if (numberCounted >= 0 && numberCounted < 1)
	{
		changeState(ONE);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 1 && numberCounted < 2)
	{
		changeState(TWO);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 2 && numberCounted < 3)
	{
		changeState(THREE);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 3 && numberCounted < 4)
	{
		changeState(FOUR);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 4 && numberCounted < 5)
	{
		changeState(FIVE);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 5 && numberCounted < 6)
	{
		changeState(SIX);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 6 && numberCounted < 7)
	{
		changeState(SEVEN);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 7 && numberCounted < 8)
	{
		changeState(EIGHT);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 8 && numberCounted < 9)
	{
		changeState(NINE);
		animationDelay += 1.0f;
	}
	if (numberCounted >= 9 && numberCounted < 10)
	{
		changeState(TEN);
		animationDelay += 1.0f;
	}
}

void MarioRef::RefVictory()
{
	victoryKO = true;
}

MarioRef::~MarioRef()
{

}
