#pragma once

enum hitFlags
{
	HIT_CREATURE = 0x1,
	HIT_BLOCKGROUP = 0x2,
	HIT_ENTITY = 0x4,
	HIT_PLAYER = 0x8,
	HIT_BOSSCREATURES = 0x10,
	HIT_ALL = 0xFFFFFFFF
};

enum hitTypes
{
	HIT_POINT = 0x1,
	HIT_BOX = 0x2,
	HIT_LINE = 0x4,
	HIT_SPHERE = 0x8,
	HIT_TREE = 0x10
};

class hitBorder
{
	public:
		hitBorder();
		virtual ~hitBorder();

		virtual bool onHit(hitBorder *target) = 0;
		//virtual void switchSpace(/*todo*/) = 0;
		//virtual hitAABB getAABB() = 0;

		hitFlags hitFlag;
		hitTypes hitType;
	protected:
};

