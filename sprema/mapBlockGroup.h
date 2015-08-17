#pragma once
#include "blockGroup.h"

//最开始的加热碰撞demo不涉及mapBlockGroup，故先放在这里不动了...

class mapBlockGroup :
	public blockGroup
{
	public:
		mapBlockGroup();
		virtual ~mapBlockGroup();
};

