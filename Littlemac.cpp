#include "Littlemac.h"
#include "Libraries.h"


const float Littlemac::SPEED = 100;
const int LEFT_SIDE_PUNCH = 1;
const int RIGHT_SIDE_PUNCH = 2;



Littlemac::Littlemac()
	: Animation(Texture::ID::Littlemac, IDLE_NB_FRAME(), 1, IDLE_START_SRC(), FRAME_SIZE())

	, currentState(IDLE)
	, isDodging (false)
	, isPunching (false)
	, comingBackfromDodgeLeft(false)
	, comingBackfromDodgeRight(false)
	, upMode(false)
	, dodgingLeft(false)
	, dodgingRight(false)
	, lowPunch(false)
	, highPunch(false)
	, comingBackFromPunch(false)
	, comingBackFromLowPunch(false)
	, isBlockingHigh(false)
	, isMoving(false)
	, inputDelay(0)
	, animationDelay(0)
	, punchConnectedLow(false)
	, punchConnectedHighLeft(false)
	, punchConnectedHighRight(false)
{
	//Start the animation on creation
	this->Play();
	//Make it loop
	this->SetIsLooping(true);
}

Littlemac::Littlemac(int x, int y, Glassjoe* gj)
	: Animation(Texture::ID::Littlemac, IDLE_NB_FRAME(), 1, IDLE_START_SRC(), FRAME_SIZE())
	, gj(gj)
	, currentState(IDLE)
	, currentX(x)
	, currentY(y)
	, isDodging(false)
	, isPunching(false)
	, comingBackfromDodgeLeft(false)
	, comingBackfromDodgeRight(false)
	, upMode(false)
	, dodgingLeft(false)
	, dodgingRight(false)
	, highPunch(false)
	, lowPunch(false)
	, comingBackFromPunch(false)
	, comingBackFromLowPunch(false)
	, isBlockingHigh(false)
	, isMoving(false)
	, inputDelay(0)
	, animationDelay(0)
	, punchConnectedLow(false)
	, punchConnectedHighLeft(false)
	, punchConnectedHighRight(false)

{
	this->SetPosition(x, y);
	//Start the animation on creation
	this->Play();
	//Make it loop
	this->SetIsLooping(true);
}

//Really basic animation state change
//You'd want to use another system to store an object's multiple animations
void Littlemac::changeState(state newState)
{
	if (this->currentState != newState)
	{
		switch (newState)
		{
		case IDLE:
			this->SetSrcPos(IDLE_START_SRC());
			this->SetNbFrame(IDLE_NB_FRAME());
			this->SetFrameRate(1);
			//Using varying frame rates cause issues since we won't instantly change to the other frame.
			break;
		case LEFTDODGE:
			this->SetSrcPos(LEFTDODGE_START_SRC());
			this->SetNbFrame(LEFTDODGE_NB_FRAME());
			this->SetFrameRate(ANIM_DEFAULT_SPEED);
			break;
		case RIGHTDODGE:
			this->SetSrcPos(RIGHTDODGE_START_SRC());
			this->SetNbFrame(RIGHTDODGE_NB_FRAME());
			this->SetFrameRate(ANIM_DEFAULT_SPEED);
			break;
		case LEFTLOWPUNCH:
			this->SetSrcPos(LEFTLOWPUNCH_START_SRC());
			this->SetNbFrame(LEFTLOWPUNCH_NB_FRAME());
			this->SetFrameRate(10);
			break;
		case LEFTHIGHPUNCH:
			this->SetSrcPos(LEFTHIGHPUNCH_START_SRC());
			this->SetNbFrame(LEFTHIGHPUNCH_NB_FRAME());
			this->SetFrameRate(8);
			break;
		case RIGHTLOWPUNCH:
			this->SetSrcPos(RIGHTLOWPUNCH_START_SRC());
			this->SetNbFrame(RIGHTLOWPUNCH_NB_FRAME());
			this->SetFrameRate(10);
			break;
		case RIGHTHIGHPUNCH:
			this->SetSrcPos(RIGHTHIGHPUNCH_START_SRC());
			this->SetNbFrame(RIGHTHIGHPUNCH_NB_FRAME());
			this->SetFrameRate(8);
			break;
		case UPPERCUT:
			this->SetSrcPos(RIGHTDODGE_START_SRC());
			this->SetNbFrame(RIGHTDODGE_NB_FRAME());
			this->SetFrameRate(5);
			break;
		case HIGHBLOCK:
			this->SetSrcPos(HIGHBLOCK_START_SRC());
			this->SetNbFrame(HIGHBLOCK_NB_FRAME());
			this->SetFrameRate(ANIM_DEFAULT_SPEED);
			break;
		case DUCK:
			this->SetSrcPos(RIGHTDODGE_START_SRC());
			this->SetNbFrame(RIGHTDODGE_NB_FRAME());
			this->SetFrameRate(ANIM_DEFAULT_SPEED);
			break;
		default:
			break;
		}
		//It's important to reset back to the first frame on change
		this->currentState = newState;
		this->ResetCurrentFrame();
	}
}

void Littlemac::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();
	int punchDir = 0;

	// Handling movement to prevent abusive input
	if (isMoving)
	{
		inputDelay -= dt;
		if (inputDelay <= 0)
		{
			inputDelay = 0;
			isMoving = false;
			
		}
	}

	if (animationDelay > 0)
	{
		animationDelay -= dt;
	}
	


	if (Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_UP))
	{
		upMode = true;
	}
	if (Engine::GetInstance()->GetInput()->IsKeyReleased(SDL_SCANCODE_UP))
	{
		upMode = false;
	}


	//Very important, otherwise our animation won't update itself
	Animation::Update();

	




	//**************************DODGE*********************************
	// Checking for dodge input
	if (!isMoving)
	{
		dodgeDir.x = Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_LEFT) ? -1 : 0 +
			Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_RIGHT) ? 1 : 0;
		dodgeDir.y = 0;
		if (dodgeDir.x == -1)
		{
			changeState(LEFTDODGE);
			isMoving = true;
			inputDelay += 0.4;
			dodgingLeft = true;
			
		}
		if (dodgeDir.x == 1)
		{
			changeState(RIGHTDODGE);
			isMoving = true;
			inputDelay += 0.4;
			dodgingRight = true;
		}
		
	}


	//Press left or right to dodge
	if (dodgeDir.x != 0){
		isDodging = true;
		
	}

	// Dodging movement
	
	if (dodgingLeft)
	{
		if (currentX > 85)
		{
			currentX -= SPEED * dt;
			SetPosition(currentX, currentY);
		}
		else
		{
			dodgingLeft = false;
			comingBackfromDodgeLeft = true;
		}
	}
	if (comingBackfromDodgeLeft)
	{
		if (currentX < 100)
		{
			currentX += SPEED * dt * 1.5f;
			SetPosition(currentX, currentY);
		}
		else
		{
			comingBackfromDodgeLeft = false;
			isDodging = false;
			changeState(IDLE);
		}
	}
	if (dodgingRight)
	{
		if (currentX < 115)
		{
			currentX += SPEED * dt;
			SetPosition(currentX, currentY);
		}
		else
		{
			dodgingRight = false;
			comingBackfromDodgeRight = true;
		}
	}
	if (comingBackfromDodgeRight)
	{
		if (currentX > 100)
		{
			currentX -= SPEED * dt * 1.5f;
			SetPosition(currentX, currentY);
		}
		else
		{
			comingBackfromDodgeRight = false;
			isDodging = false;
			changeState(IDLE);
		}
	}


	//**************************PUNCH*********************************

	if (!isMoving)
	{

		punchDir = Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_Z) ? -1 : 0 +
			Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_X) ? 1 : 0;

		if (punchDir == -1)
		{
			isPunching = true;

			if (upMode)
			{
				changeState(LEFTHIGHPUNCH);
				highPunch = true;
				punchConnectedHighLeft = true;
				inputDelay += 0.3;
				isMoving = true;
				animationDelay += 0.18;
			}
			else
			{
				changeState(LEFTLOWPUNCH);
				lowPunch = true;
				punchConnectedLow = true;
				inputDelay += 0.3;
				isMoving = true;
				animationDelay += 0.18;
			}
			
		}


		if (punchDir == 1)
		{
			isPunching = true;

			if (upMode)
			{
				changeState(RIGHTHIGHPUNCH);
				highPunch = true;
				punchConnectedHighRight = true;
				inputDelay += 0.3;
				isMoving = true;
				animationDelay += 0.18;
			}
			else
			{
				changeState(RIGHTLOWPUNCH);
				lowPunch = true;
				punchConnectedLow = true;
				inputDelay += 0.3;
				isMoving = true;
				animationDelay += 0.18;
			}
			
		}
		
	}

	if (highPunch)
	{
		

		if (currentY > 100)
		{
			currentY -= SPEED * dt * 1.5f;
			SetPosition(currentX, currentY);
		}
		else
		{
			
			highPunch = false;
			comingBackFromPunch = true;

			
		}
	}
	if (comingBackFromPunch)
	{
		
		if (currentY < 119)
		{
			
			currentY += SPEED * dt * 1.5f;
			SetPosition(currentX, currentY);
		}
		else
		{
			comingBackFromPunch = false;
			isPunching = false;
			changeState(IDLE);
		}
	}

	if (lowPunch)
	{
		if (currentY > 112)
		{
			currentY -= SPEED * dt * 0.5;
			SetPosition(currentX, currentY);
		}
		else
		{
			lowPunch = false;
			comingBackFromPunch = true;
		}
	}
	if (comingBackFromLowPunch)
	{
		if (currentY < 119)
		{
			currentY += SPEED * dt * 0.5;
			SetPosition(currentX, currentY);
		}
		else
		{
			comingBackFromLowPunch = false;
			isPunching = false;
			changeState(IDLE);
		}
	}

	if (gj->GetProtectedState() == false && punchConnectedHighLeft == true && animationDelay <= 0)
	{
		std::cout << "CONNECTS HIGH LEFT!" << std::endl;
		gj->GetsPunchedHighLeft();
		punchConnectedHighLeft = false;
	}

	if (gj->GetProtectedState() == false && punchConnectedHighRight == true && animationDelay <= 0)
	{
		std::cout << "CONNECTS HIGH RIGHT!" << std::endl;
		gj->GetsPunchedHighRight();
		punchConnectedHighRight = false;
	}

	if (gj->GetProtectedState() == false && punchConnectedLow == true && animationDelay <= 0)
	{
		std::cout << "CONNECTS LOW!" << std::endl;
		gj->GetsPunchedLow();
		punchConnectedLow = false;
	}

	
	


	//**************************BLOCK*********************************

	if (!isMoving)
	{
		if (Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_DOWN))
		{
			changeState(HIGHBLOCK);
			isBlockingHigh = true;
		}
	}

	if (Engine::GetInstance()->GetInput()->IsKeyReleased(SDL_SCANCODE_DOWN))
	{
		changeState(IDLE);
		isBlockingHigh = false;
	}



	//Don't mind the brackets. Simply tried to save some screen space.
	//Press Space to Pause & Resume
	if (Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_SPACE)){
		if (this->GetIsPlaying()){
			this->Stop();
		}
		else {
			this->Play();
		}
	}



}


Littlemac::~Littlemac()
{

}