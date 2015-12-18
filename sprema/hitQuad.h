#pragma once
#include "hitBorder.h"
class hitQuad :
	public hitBorder
{
	public:
		hitQuad();
		virtual ~hitQuad();

		virtual bool onHit(hitBorder *target);
		//virtual void switchSpace(/*todo*/) = 0;
		//virtual hitAABB getAABB() = 0;
};

