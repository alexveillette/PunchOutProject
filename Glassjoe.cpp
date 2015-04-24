#include "Glassjoe.h"
#include "Libraries.h"



Glassjoe::Glassjoe()
	: Animation(Texture::ID::Glassjoe, IDLE_NB_FRAME(), 3, IDLE_START_SRC(), FRAME_SIZE())
{
	//Start the animation on creation
	this->Play();
	//Make it loop
	this->SetIsLooping(true);
}

Glassjoe::Glassjoe(int x, int y)
	: Animation(Texture::ID::Glassjoe, IDLE_NB_FRAME(), 4, IDLE_START_SRC(), FRAME_SIZE())
	, currentState(IDLE)
	, currentX(x)
	, currentY(y)
	, isProtectedLow(true)
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
			this->SetFrameRate(3);
			break;
		case JABPUNCH:
			this->SetSrcPos(JABPUNCH_START_SRC());
			this->SetNbFrame(JABPUNCH_NB_FRAME());
			this->SetFrameRate(3);
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
	//Very important, otherwise our animation won't update itself
	Animation::Update();

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

void Glassjoe::GetsPunchedLow()
{
	std::cout << "OUCH LOW" << std::endl;
	this->changeState(GETSPUNCHED_LOW);

}
void Glassjoe::GetsPunchedHighLeft()
{
	std::cout << "OUCH HIGH LEFT" << std::endl;
	this->changeState(GETSPUNCHED_HIGHLEFT);
}
void Glassjoe::GetsPunchedHighRight()
{
	std::cout << "OUCH HIGH RIGHT" << std::endl;
	this->changeState(GETSPUNCHED_HIGHRIGHT);
}

void Glassjoe::SuccessfulBlockLow()
{
	std::cout << "HAHA BLOCK LOW" << std::endl;
	this->changeState(BLOCK_LOW);

}
void Glassjoe::SuccessfulBlockHigh()
{
	std::cout << "HAHA BLOCK HIGH" << std::endl;
	this->changeState(BLOCK_HIGH);
}


Glassjoe::~Glassjoe()
{

}
