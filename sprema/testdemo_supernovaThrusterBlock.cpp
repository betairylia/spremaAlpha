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
	group.addMass(10);//�ƽ���������Ϊ10����Ϊ��������ռ�����ӣ�
	//todo������ƽ��¼�
}

void testdemo_supernovaThrusterBlock::onLeave(blockGroup & group)
{
	group.removeMass(10);
}
