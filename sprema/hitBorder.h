#pragma once
class hitBorder
{
	public:
		hitBorder();
		virtual ~hitBorder();

		virtual bool onHit(hitBorder *target) = 0;
		virtual void switchSpace(/*todo*/) = 0;
		//virtual hitAABB getAABB() = 0;
};

