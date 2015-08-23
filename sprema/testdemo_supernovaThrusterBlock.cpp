#include "testdemo_supernovaThrusterBlock.h"
#include "blockGroup.h"


testdemo_supernovaThrusterBlock::testdemo_supernovaThrusterBlock()
{
}


testdemo_supernovaThrusterBlock::~testdemo_supernovaThrusterBlock()
{
}

void testdemo_supernovaThrusterBlock::onJoin(blockGroup & group)
{
	group.addMass(10);//推进器的质量为10（因为它并不会占满格子）
	//todo：添加推进事件
}

void testdemo_supernovaThrusterBlock::onLeave(blockGroup & group)
{
	group.removeMass(10);
}
