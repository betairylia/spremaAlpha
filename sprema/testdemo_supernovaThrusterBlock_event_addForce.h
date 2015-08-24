#pragma once
#include "spremaEvent.h"
class testdemo_supernovaThrusterBlock_event_addForce :
	public spremaEvent
{
	public:
		testdemo_supernovaThrusterBlock_event_addForce(block* srcBlock);
		virtual ~testdemo_supernovaThrusterBlock_event_addForce();

		//override
		virtual void onTimer();

	private:
		float targetSpeed = 2.0;
};

