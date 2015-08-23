#include "testdemo_grassBlock.h"
#include "blockGroup.h"


testdemo_grassBlock::testdemo_grassBlock()
{
}


testdemo_grassBlock::~testdemo_grassBlock()
{
}

void testdemo_grassBlock::onJoin(blockGroup & group)
{
	group.addMass(15);//草的质量为15（以密度1.5计算（带有泥土）；一个水方块的质量为10）
}

void testdemo_grassBlock::onLeave(blockGroup & group)
{
	group.removeMass(15);
}
