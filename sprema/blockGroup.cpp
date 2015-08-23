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
	放置方块。
	通过map找到相对应的blockGroupStorage，并调用其setBlock方法。
	*/

	//先计算坐标对应的blockGroupStorageID。（chunk坐标）
	int Cx = x / CHUNK_SIZEX;
	int Cy = y / CHUNK_SIZEY;
	int Cz = z / CHUNK_SIZEZ;
	int key = (Cx << 20) + (Cy << 10) + (Cz);//chunk坐标不能超过1024 (blockGroup大小限定为1024*CHUNK_SIZE^3)

	//根据key查找是否存在对应的存储器。如果没有则创建一个。
	if (storeMap.count(key) == 0 || storeMap[key] == nullptr)
	{
		storeMap[key] = new blockGroupStorage();//构造函数
		//如果必要，在此处执行相应的存储器初始化过程。
	}

	block* tmp = storeMap[key]->setBlock(x % CHUNK_SIZEX, y % CHUNK_SIZEY, z % CHUNK_SIZEZ, targetBlock);

	//告诉方块它被放进去了，注册相关事件。
	targetBlock.onJoin((*this));

	//如果发生替换，告诉那个被替换掉的方块它被踢出去了，注销相关事件。
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
