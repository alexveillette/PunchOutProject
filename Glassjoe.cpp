#include "Glassjoe.h"
#include "Libraries.h"

const float Glassjoe::SPEED = 100;

Glassjoe::Glassjoe()
	: Animation(Texture::ID::Glassjoe, IDLE_NB_FRAME(), 3, IDLE_START_SRC(), FRAME_SIZE())
{
	//Start the animation on creation
	this->Play();
	//Make it loop
	this->SetIsLooping(true);
}

Glassjoe::Glassjoe(int x, int y, GlassJoeBody* gjb)
	: Animation(Texture::ID::Glassjoe, COCKY_NB_FRAME(), 4, COCKY_START_SRC(), FRAME_SIZE())
	, currentState(COCKY)
	, currentX(x)
	, currentY(y)
	, isProtectedLow(true)
	, enabled(false)
	, isDown(false)
	, numberToCount(0)
	, finalKO(false)
	, gjb(gjb)
	, decisionTimer(4.0)
	, dizzy(false)
	, isPunchingHook(false)
	, isPunchingJab(false)
	, isInvincible(false)
{
	this->SetPosition(x, y);
	//Start the animation on creation
	this->Play();
	//Make it loop
	this->SetIsLooping(true);
}

//Really basic animation state change
//You'd want to use another system to store an object's multiple animations
void Glassjoe::changeState(state newState)
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
		case HOOKPUNCH:
			this->SetSrcPos(HOOKPUNCH_START_SRC());
			this->SetNbFrame(HOOKPUNCH_NB_FRAME());
			this->SetFrameRate(7);
			break;
		case JABPUNCH:
			this->SetSrcPos(JABPUNCH_START_SRC());
			this->SetNbFrame(JABPUNCH_NB_FRAME());
			this->SetFrameRate(7);
			break;
		case GETSPUNCHED_LOW:
			this->SetSrcPos(GETSPUNCHED_LOW_START_SRC());
			this->SetNbFrame(GETSPUNCHED_LOW_NB_FRAME());
			this->SetFrameRate(3);
			break;
		case GETSPUNCHED_HIGHLEFT:
			this->SetSrcPos(GETSPUNCHED_HIGHLEFT_START_SRC());
			this->SetNbFrame(GETSPUNCHED_HIGHLEFT_NB_FRAME());
			this->SetFrameRate(3);
			break;
		case GETSPUNCHED_HIGHRIGHT:
			this->SetSrcPos(GETSPUNCHED_HIGHRIGHT_START_SRC());
			this->SetNbFrame(GETSPUNCHED_HIGHRIGHT_NB_FRAME());
			this->SetFrameRate(3);
			break;
		case BLOCK_LOW:
			this->SetSrcPos(BLOCK_LOW_START_SRC());
			this->SetNbFrame(BLOCK_LOW_NB_FRAME());
			this->SetFrameRate(2);
			break;
		case BLOCK_HIGH:
			this->SetSrcPos(BLOCK_HIGH_START_SRC());
			this->SetNbFrame(BLOCK_HIGH_NB_FRAME());
			this->SetFrameRate(3);
			break;
		case FLYING:
			this->SetSrcPos(FLYING_START_SRC());
			this->SetNbFrame(FLYING_NB_FRAME());
			this->SetFrameRate(3);
			break;
		case KNOCKED_DOWN:
			this->SetSrcPos(KNOCKED_DOWN_START_SRC());
			this->SetNbFrame(KNOCKED_DOWN_NB_FRAME());
			this->SetFrameRate(3);
			break;
		case COCKY:
			this->SetSrcPos(COCKY_START_SRC());
			this->SetNbFrame(COCKY_NB_FRAME());
			this->SetFrameRate(3);
			break;
		case WARMUP:
			this->SetSrcPos(WARMUP_START_SRC());
			this->SetNbFrame(WARMUP_NB_FRAME());
			this->SetFrameRate(6);
			break;
		case GETSUP:
			this->SetSrcPos(GETSUP_START_SRC());
			this->SetNbFrame(GETSUP_NB_FRAME());
			this->SetFrameRate(1);
			break;
		case DIZZY:
			this->SetSrcPos(DIZZY_START_SRC());
			this->SetNbFrame(DIZZY_NB_FRAME());
			this->SetFrameRate(1);
			break;
		case IDLE_HIGH:
			this->SetSrcPos(IDLE_HIGH_START_SRC());
			this->SetNbFrame(IDLE_HIGH_NB_FRAME());
			this->SetFrameRate(3);
			break;

		default:
			break;
		}
		//It's important to reset back to the first frame on change
		this->currentState = newState;
		this->ResetCurrentFrame();
	}
}

void Glassjoe::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

	// MAIN DECISION LOOP

	if (enabled == true)
	{
		if (animationDelay > 0)
		{
			animationDelay -= dt;

			if (dizzy == true && animationDelay <= 0)
			{
				animationDelay = 0.5f;
				changeState(DIZZY);
				dizzy = false;
			}
			else if (dizzy == false && animationDelay <= 0)
			{
				animationDelay = 0;

				if (isPunchingHook == true && animationDelay <= 0)
				{
					isPunchingHook = false;
					hookLands = true;
					isInvincible = false;
					animationDelay += 0.2f;

				}

				if (isPunchingJab == true && animationDelay <= 0)
				{
					isPunchingJab = false;
					jabLands = true;
					isInvincible = false;
					animationDelay += 0.2f;

				}

				if (isProtectedLow == true && animationDelay <= 0)
				{
					jabLands = false;
					hookLands = false;
					changeState(IDLE);

				}

				else if (isProtectedHigh == true && animationDelay <= 0)
				{
					changeState(IDLE_HIGH);
					jabLands = false;
					hookLands = false;

				}
			}

			
		}

		decisionTimer -= dt;

		if (decisionTimer <= 0)
		{
			MakesDecision();
		}
	}







	// START OF GAME

	if (getsToCenterOfRing == true)
	{
		

		if (animationDelay > 0)
		{
			animationDelay -= dt;
		}


		if (animationDelay <= 0)
		{
			changeState(WARMUP);

			if (currentY < 67)
			{
				currentY += SPEED * dt * 0.1f;
				SetPosition(currentX, currentY);
			}


			if (currentX > 110)
			{
				currentX -= SPEED * dt * 0.2f;
				SetPosition(currentX, currentY);
			}
			else
			{
				getsToCenterOfRing = false;
				changeState(IDLE);
				AudioSys->PlayMusic(Musics->Get(Music::ID::PunchOutMusic));
				enabled = true;
			}
		}
	}
	


		// KNOCKDOWN CONDITIONS - ANIMATIONS, ETC.
	if (getsKnockedDown == true)
	{
		if (currentX > 30)
		{
			currentX -= SPEED * dt * 0.3f;
			SetPosition(currentX, currentY);
		}

		if (currentY > 53)
		{
			currentY -= SPEED * dt * 0.05f;
			SetPosition(currentX, currentY);
		}
		else if (currentX <= 30 && currentY <= 53)
		{
			getsKnockedDown = false;
			changeState(KNOCKED_DOWN);
			SetPosition(28, 30);
			gjb->SetPosition(62, 70);
			if (finalKO == true)
			{
				isDown = false;
			}
			else
			{
				isDown = true;
			}
			
			
		}
	}

	if (isDown == true)
	{
		if (numberToCount > 0)
		{
			numberToCount -= dt;
		}
		
		if (numberToCount <= 0)
		{
			changeState(GETSUP);
			SetPosition(30, 23);
			gjb->SetPosition(-100, -100);
			animationDelay += 1.0f;
			isDown = false;
			getsBackUp = true;
		}
	}
	if (getsBackUp == true)
	{
		if (animationDelay > 0)
		{
			animationDelay -= dt;
		}
		if (animationDelay <= 0)
		{
			changeState(WARMUP);
			SetPosition(30, 13);
			getsBackUp = false;
			isUp = true;
			animationDelay + 5.0f;
		}

	}
	if (isUp == true)
	{
		if (animationDelay > 0)
		{
			animationDelay -= dt;
		}

			if (currentY < 67)
			{
				currentY += SPEED * dt * 0.08f;
				SetPosition(currentX, currentY);
			}


			if (currentX < 110)
			{
				currentX += SPEED * dt * 0.3f;
				SetPosition(currentX, currentY);
			}
			else
			{
				isUp = false;
				changeState(IDLE);
				AudioSys->PlayMusic(Musics->Get(Music::ID::PunchOutMusic));
				numberToCount = 0;
				enabled = true;
			}
		
	}
	
		
	
		//Very important, otherwise our animation won't update itself
		Animation::Update();

	
}

void Glassjoe::MakesDecision()
{

	// EVERY 3 SECONDS, GLASS JOE MAKES A DECISION : PUNCH, JAB, BLOCK HIGH OR BLOCK LOW

	int possibleAction = rand() % 3;

	if (possibleAction == 0)
	{
		// BLOCKS HIGH IF BLOCKING LOW, VICE VERSA
		if (isProtectedLow == true)
		{
			isProtectedLow = false;
			isProtectedHigh = true;
			changeState(IDLE_HIGH);
		}
		else
		{
			isProtectedLow = true;
			isProtectedHigh = false;
			changeState(IDLE);
		}
	}
	else if (possibleAction == 1)
	{
		isInvincible = true;
		isPunchingHook = true;
		changeState(HOOKPUNCH);
		animationDelay = 1.0f;
	}
	else if (possibleAction == 2)
	{
		isInvincible = true;
		isPunchingJab = true;
		changeState(JABPUNCH);
		animationDelay = 0.8f;
	}

	decisionTimer += 3.0f;
}

void Glassjoe::GetsPunchedLow()
{

	this->changeState(GETSPUNCHED_LOW);
	dizzy = true;
	animationDelay = 0.5f;

}
void Glassjoe::GetsPunchedHighLeft()
{
	this->changeState(GETSPUNCHED_HIGHLEFT);
	dizzy = true;
	animationDelay = 0.5f;
}
void Glassjoe::GetsPunchedHighRight()
{

	this->changeState(GETSPUNCHED_HIGHRIGHT);
	dizzy = true;
	animationDelay = 0.5f;
}

void Glassjoe::SuccessfulBlockLow()
{

	this->changeState(BLOCK_LOW);
	animationDelay = 0.5f;
}
void Glassjoe::SuccessfulBlockHigh()
{

	this->changeState(BLOCK_HIGH);
	animationDelay = 0.5f;
}

void Glassjoe::GetsToCenterOfRing()
{
	animationDelay = 5.0f;
	getsToCenterOfRing = true;
}

void Glassjoe::GetsKnockedDown(int countNumber)
{
	enabled = false;
	animationDelay = 2.0f;
	this->changeState(FLYING);
	getsKnockedDown = true;
	AudioSys->PlayMusic(Musics->Get(Music::ID::GlassJoeKO));
	numberToCount = countNumber;
}

void Glassjoe::FinalKnockdown()
{
	finalKO = true;
}

void Glassjoe::Victory()
{
	this->changeState(COCKY);
}

Glassjoe::~Glassjoe()
{

}
