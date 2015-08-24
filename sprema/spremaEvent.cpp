#include "spremaEvent.h"

spremaEvent::spremaEvent(block * srcBlock)
{
}

spremaEvent::~spremaEvent()
{
}

void spremaEvent::update(float dt)
{
	timeRemaining -= dt;
	if (timeRemaining <= 0)
	{
		onTimer();
		timeRemaining = ((float)rand() / 32768) * (timeRemainingMax - timeRemainingMin) + timeRemainingMin;
	}
	return;
}