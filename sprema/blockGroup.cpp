#include "blockGroup.h"



blockGroup::blockGroup()
{
	//todo
}


blockGroup::~blockGroup()
{
	//todo
}

void blockGroup::update()
{
	//todo
	//����ע�������event��
	for (auto targetEvent = eventMap.begin(); targetEvent != eventMap.end(); targetEvent++)
	{
		//***********��������ӦΪ��ǰ֡����һ֡���ʱ���***********//
		targetEvent->second.update(0.01);
		//***********��������ӦΪ��ǰ֡����һ֡���ʱ���***********//
	}
}

void blockGroup::render()
{
	//todo
}

void blockGroup::attachForces(list<force>& forces)
{
	//todo
}

list<force>* blockGroup::getImpactForces()
{
	return nullptr;
}

void blockGroup::loadFile()
{
}

void blockGroup::saveFile()
{
}

block* blockGroup::setBlock(int x, int y, int z, block & targetBlock)
{
	/*
	���÷��顣
	ͨ��map�ҵ����Ӧ��blockGroupStorage����������setBlock������
	*/

	//�ȼ��������Ӧ��blockGroupStorageID����chunk���꣩
	int Cx = x / CHUNK_SIZEX;
	int Cy = y / CHUNK_SIZEY;
	int Cz = z / CHUNK_SIZEZ;
	int key = (Cx << 20) + (Cy << 10) + (Cz);//chunk���겻�ܳ���1024 (blockGroup��С�޶�Ϊ1024*CHUNK_SIZE^3)

	//����key�����Ƿ���ڶ�Ӧ�Ĵ洢�������û���򴴽�һ����
	if (storeMap.count(key) == 0 || storeMap[key] == nullptr)
	{
		storeMap[key] = new blockGroupStorage();//���캯��
		//�����Ҫ���ڴ˴�ִ����Ӧ�Ĵ洢����ʼ�����̡�
	}

	block* tmp = storeMap[key]->setBlock(x % CHUNK_SIZEX, y % CHUNK_SIZEY, z % CHUNK_SIZEZ, targetBlock);

	//���߷��������Ž�ȥ�ˣ�ע������¼���
	targetBlock.onJoin((*this));

	//��������滻�������Ǹ����滻���ķ��������߳�ȥ�ˣ�ע������¼���
	if (tmp != nullptr)
	{
		tmp->onLeave((*this));
	}

	return tmp;
}

void blockGroup::blockUpdateCompleted(/*�ʵ��Ĳ���*/)
{
}

double blockGroup::addMass(double amount)
{
	mass += amount;
	return mass;
}

double blockGroup::removeMass(double amount)
{
	mass -= amount;
	return mass;
}

int blockGroup::addEvent(spremaEvent & targetEvent)
{
	while (1)
	{
		//���һ����ֵ
		int key = rand();
		
		//����ü�ֵδ��ʹ�ã���ռ������
		if (eventMap.count(key) == 0)
		{
			eventMap[key] = targetEvent;
			return key;
		}
		//�������ѭ����ֱ���ҵ�һ������ʹ�õļ�ֵΪֹ��
	}
	return 0;
}

void blockGroup::removeEvent(int eventID)
{
	if (eventMap.count(eventID) == 0)//�ü�ֵ�����ڣ�ֱ�ӽ���������
		return;
	
	spremaEvent& eventTmp = eventMap[eventID];
	eventMap.erase(eventID);
	delete (&eventTmp);

	return;
}
