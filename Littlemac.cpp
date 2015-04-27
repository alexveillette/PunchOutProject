#include "Littlemac.h"
#include "Libraries.h"


const float Littlemac::SPEED = 100;
const int LEFT_SIDE_PUNCH = 1;
const int RIGHT_SIDE_PUNCH = 2;



Littlemac::Littlemac()
	: Animation(Texture::ID::Littlemac, IDLE_NB_FRAME(), 1, IDLE_START_SRC(), FRAME_SIZE())
{
	//Start the animation on creation
	this->Play();
	//Make it loop
	this->SetIsLooping(true);
}

Littlemac::Littlemac(int x, int y, Glassjoe* gj, Hearts* hearts, Stars* stars, Points* points, LittleMacHealth* lmHealth, GlassJoeHealth* gjHealth, TitleScreen* ts, MarioRef* mr, PunchOutTimer* POTimer, GameOverScreen* goScreen, VictoryScreen* viScreen)
	: Animation(Texture::ID::Littlemac, IDLE_NB_FRAME(), 1, IDLE_START_SRC(), FRAME_SIZE())
	, gj(gj)
	, ts(ts)
	, hearts(hearts)
	, stars(stars)
	, points(points)
	, lmHealth(lmHealth)
	, gjHealth(gjHealth)
	, mr(mr)
	, POTimer(POTimer)
	, goScreen(goScreen)
	, viScreen(viScreen)
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
	, enabled(false)
	, startGame(false)
	, glassJoeKnockedDown(false)
	, numberOfKO(0)
	, victoryBool(false)
	, getsPunched(false)
	, knockedOut(false)

{
	this->SetPosition(-100, 120);
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
		case VICTORY:
			this->SetSrcPos(VICTORY_START_SRC());
			this->SetNbFrame(VICTORY_NB_FRAME());
			this->SetFrameRate(6);
			break;
		case KNOCKEDOUT:
			this->SetSrcPos(KNOCKEDOUT_START_SRC());
			this->SetNbFrame(KNOCKEDOUT_NB_FRAME());
			this->SetFrameRate(1);
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

	// GAME START
	if (startGame ==  false)
	{
		if (inputDelay > 0)
		{
			inputDelay -= dt;
			if (inputDelay <= 0)
			{
				inputDelay = 0;
			}
		}
		if (Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_RETURN))
		{
			
			inputDelay += 9.0f;
			AudioSys->PlayMusic(Musics->Get(Music::ID::GlassJoeIntro));
			ts->SetPosition(-300, -300);
			this->SetPosition(100, 120);
			gj->GetsToCenterOfRing();
			gameStarting = true;
		}
		if (inputDelay <= 0 && gameStarting == true)
		{
			inputDelay = 0;
			enabled = true;
			startGame = true;
			isMoving = true;
			mr->FightAndLeaves();
			gameStarting = false;
			POTimer->isStarted();

		}
		
		
	}

	Animation::Update();

	if (enabled)
	{
		
		int punchDir = 0;

		// Handling movement to prevent abusive input
		if (isMoving)
		{
			if (knockedOut == true)
			{
				if (currentY < 250)
				{
					currentY += SPEED * dt * 0.5;
					SetPosition(currentX, currentY);
					gj->SetActiveState(false);
				}
			}
			inputDelay -= dt;

				if (inputDelay <= 0)
				{
					if (glassJoeKnockedDown == true && victoryBool == false)
					{
						gjHealth->RestoreHealth();
						glassJoeKnockedDown = false;
						POTimer->isStarted();
					}

					if (victoryBool == true)
					{
						changeState(VICTORY);
						victoryBool = false;
						inputDelay += 5.0f;
						hasWon = true;
						enabled = false;
						viScreen->Arrives();
					}

					if (knockedOut == true)
					{

						gj->Victory();
						goScreen->Arrives();
					}

					inputDelay = 0;
					isMoving = false;	
			}
		}

		// Manage delay of animations to make them mesh
		if (animationDelay > 0)
		{
			animationDelay -= dt;
		}

		// High punch enabled or disabled

		if (Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_UP))
		{
			upMode = true;
		}
		if (Engine::GetInstance()->GetInput()->IsKeyReleased(SDL_SCANCODE_UP))
		{
			upMode = false;
		}




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


		// Dodging movement

		if (dodgingLeft)
		{
			isDodging = true;
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

		// Coming back from dodge movement
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
			isDodging = true;
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

			// Checking for punch input

			punchDir = Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_Z) ? -1 : 0 +
				Engine::GetInstance()->GetInput()->IsKeyPressed(SDL_SCANCODE_X) ? 1 : 0;

			// Left punch
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

			// Right punch

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

		// Managing punch movement

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

		// Punch RESULTS - Glass Joe is blocking LOW

		if (gj->GetProtectedStateLow() == true && animationDelay <= 0)
		{
			if (punchConnectedHighLeft && gj->GetInvincibleState() == false)
			{
				gj->GetsPunchedHighLeft();
				AudioSys->PlaySound(Sounds->Get(Sound::ID::EnemyHit));
				punchConnectedHighLeft = false;
				gjHealth->LosesSmallHealth();
				points->PunchPoints();
				//CHECK FOR KO
				CheckForKO();
				
			}
			if (punchConnectedHighRight && gj->GetInvincibleState() == false)
			{
				gj->GetsPunchedHighRight();
				AudioSys->PlaySound(Sounds->Get(Sound::ID::EnemyHit));
				punchConnectedHighRight = false;
				gjHealth->LosesSmallHealth();
				points->PunchPoints();
				//CHECK FOR KO

				CheckForKO();
			}
			if (punchConnectedLow)
			{
				//BLOCKS
				gj->SuccessfulBlockLow();
				punchConnectedLow = false;
				inputDelay += 0.5f;
				hearts->LosesHeart();
			}
			else
			{
				punchConnectedHighRight = false;
				punchConnectedHighLeft = false;
				punchConnectedLow = false;
			}

		}

		// Punch RESULTS - Glass Joe is blocking HIGH

		if (gj->GetProtectedStateHigh() == true && animationDelay <= 0)
		{
			if (punchConnectedHighLeft)
			{
				//BLOCKS
				gj->SuccessfulBlockHigh();
				punchConnectedHighLeft = false;
				hearts->LosesHeart();
				inputDelay += 0.5f;
			}
			if (punchConnectedHighRight)
			{
				//BLOCKS
				gj->SuccessfulBlockHigh();
				punchConnectedHighRight = false;
				hearts->LosesHeart();
				inputDelay += 0.5f;
			}
			if (punchConnectedLow && gj->GetInvincibleState() == false)
			{

				gj->GetsPunchedLow();
				AudioSys->PlaySound(Sounds->Get(Sound::ID::EnemyHit));
				punchConnectedLow = false;
				gjHealth->LosesSmallHealth();
				points->PunchPoints();

				//CHECK FOR KO

				CheckForKO();
			}
			else
			{
				punchConnectedHighRight = false;
				punchConnectedHighLeft = false;
				punchConnectedLow = false;
			}
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

		// ***********************GLASS JOE PUNCHES***********************

		if (gj->GetHookState() == true || gj->GetJabState() == true)
		{
			if (!getsPunched)
			{
				if (isBlockingHigh == false && isDodging == false)
				{
					getsPunched = true;
					ReceivesPunch();
				}
				else
				{
					gj->SetHookState(false);
					gj->SetJabState(false);
				}
			}
		}
	}
}

void Littlemac::IsEnabled()
{
	enabled = true;
}

void Littlemac::IsDisabled()
{
	enabled = false;
}

void Littlemac::CheckForKO()
{
	isMoving = true;

	if (gjHealth->GetHealthQuantity() <= 0)
	{
		int countNumber = rand() % 7 + 3;
		inputDelay += countNumber + 10.0f;
		gjHealth->SetHealthQuantity(0);
		gj->GetsKnockedDown(countNumber);
		mr->ComesToCount(countNumber);
		glassJoeKnockedDown = true;
		POTimer->isStopped();

		//VICTORY CHECK
		numberOfKO++;
		if (numberOfKO >= 3)
		{
			Victory(countNumber);
			
		}
	}
}

// VICTORY
void Littlemac::Victory(int countNumber)
{
	mr->RefVictory();
	gj->FinalKnockdown();
	isMoving = true;
	inputDelay -= (countNumber + 6.5f);
	victoryBool = true;
}

void Littlemac::ReceivesPunch()
{
	int countNumber = rand() % 7 + 3;
	AudioSys->PlaySound(Sounds->Get(Sound::ID::EnemyHit));
	gj->SetHookState(false);
	gj->SetJabState(false);
	getsPunched = false;
	lmHealth->LosesSmallHealth();


	//GAME OVER
	if (lmHealth->GetHealthQuantity() <= 0)
	{
		knockedOut = true;
		isMoving = true;
		AudioSys->PlayMusic(Musics->Get(Music::ID::LittleMacKO));
		inputDelay += 4.0f;
		gj->SetActiveState(false);
		mr->ComesToCount(countNumber);
		mr->RefVictory();
		POTimer->isStopped();
		changeState(KNOCKEDOUT);
	}
}
Littlemac::~Littlemac()
{

}