#include "testdemo_supernovaThrusterBlock.h"
#include "testdemo_supernovaThrusterBlock_event_addForce.h"
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
	
	//����Ӧ�ø�Ϊ�ܵ����������ӡ�
	testdemo_supernovaThrusterBlock_event_addForce& eAddForce = (*(new testdemo_supernovaThrusterBlock_event_addForce(this)));
	eventID = group.addEvent(eAddForce);
}

void testdemo_supernovaThrusterBlock::onLeave(blockGroup & group)
{
	group.removeMass(10);
	group.removeEvent(eventID);
}
