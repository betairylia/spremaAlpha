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
	group.addMass(15);//�ݵ�����Ϊ15�����ܶ�1.5���㣨������������һ��ˮ���������Ϊ10��
}

void testdemo_grassBlock::onLeave(blockGroup & group)
{
	group.removeMass(15);
}
