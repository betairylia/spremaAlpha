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
}

void blockGroup::render()
{
	//todo
}

void blockGroup::attachForces(list<force>& forces)
{
	//todo
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

double blockGroup::addMass(double amount)
{
	mass += amount;
	return mass;
}

void blockGroup::addEvent(spremaEvent & event)
{
}

double blockGroup::removeMass(double amount)
{
	mass -= amount;
	return mass;
}

void blockGroup::removeEvent(spremaEvent & event)
{
}
