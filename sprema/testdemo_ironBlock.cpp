#include "testdemo_ironBlock.h"
#include "blockGroup.h"


testdemo_ironBlock::testdemo_ironBlock()
{
}


testdemo_ironBlock::~testdemo_ironBlock()
{
}

void testdemo_ironBlock::onJoin(blockGroup & group)
{
	group.addMass(78);//铁的质量为78;
}

void testdemo_ironBlock::onLeave(blockGroup & group)
{
	group.removeMass(78);
}
