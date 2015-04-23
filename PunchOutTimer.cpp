#include "PunchOutTimer.h"
#include "Libraries.h"


std::stringstream ss;

PunchOutTimer::PunchOutTimer()
	:Text("", Font::ID::Dialog, 700)
	, minutes(0)
	, secondsTen(0)
	, secondsOne(0)
	, started(true)
	, elapsedTime(0)
	 
{
	SetPosition(209, 18);
	this->Scale(0.4);
	
	SetText(ss.str());
}

PunchOutTimer::~PunchOutTimer()
{
}

void PunchOutTimer::Start()
{
}

void PunchOutTimer::Update()
{
	float dt = Engine::GetInstance()->GetTimer()->GetDeltaTime();

	ss << minutes << ":" << secondsTen << (int) secondsOne;
	
	secondsOne += dt * 2;	
	

	if (secondsOne >= 10)
	{
		secondsOne = 0;
		secondsTen++;
	}
	if (secondsTen >= 6)
	{
		secondsTen = 0;
		minutes++;
	}

	SetText(ss.str());
	Text::Update();
	ss.str(std::string());
}

void PunchOutTimer::Stop()
{
}