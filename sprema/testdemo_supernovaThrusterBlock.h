#pragma once
#include "block.h"
class testdemo_supernovaThrusterBlock :
	public block
{
	public:
		testdemo_supernovaThrusterBlock();
		virtual ~testdemo_supernovaThrusterBlock();

		virtual void onJoin(blockGroup& group);//当方块被加入方块组时，向其中注册事件。
		virtual void onLeave(blockGroup& group);//当方块从方块组中脱离时，从其中注销事件。

	private:
		int eventID;
};

