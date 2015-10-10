#include "blockGroup.h"
#include "hitTree.h"


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
	//更新注册的所有event。
	for (auto targetEvent = eventMap.begin(); targetEvent != eventMap.end(); targetEvent++)
	{
		//***********函数参数应为当前帧与上一帧间的时间差***********//
		targetEvent->second.update(0.01);
		//***********函数参数应为当前帧与上一帧间的时间差***********//
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
	list<force>* listA = new list<force>();
	getImpactForces_d(listA, hitTarget);

	//normalize
	double total = 0, rate = 1.00;
	for each(auto frc in (*listA))
	{
		total += frc.numberValue;
	}

	//TODO:计算rate
	for each(auto frc in (*listA))
	{
		frc.factor = rate;
	}

	return listA;
}

void blockGroup::getImpactForces_d(list<force>* listA, hitBorder* hit)
{
	if (hit->hitType == HIT_TREE)
	{
		for each (auto iter in static_cast<hitTree*>(hit)->child)
		{
			if (iter.second)
			{
				getImpactForces_d(listA, iter.first);
			}
		}
	}
	else
	{
		listA->merge(hit->dObject->getImpactForces);
	}
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

void blockGroup::blockUpdateCompleted(/*适当的参数*/)
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
		//随机一个键值
		int key = rand();
		
		//如果该键值未被使用，则占据它。
		if (eventMap.count(key) == 0)
		{
			eventMap[key] = targetEvent;
			return key;
		}
		//否则继续循环，直到找到一个可以使用的键值为止。
	}
	return 0;
}

void blockGroup::removeEvent(int eventID)
{
	if (eventMap.count(eventID) == 0)//该键值不存在，直接结束函数。
		return;
	
	spremaEvent& eventTmp = eventMap[eventID];
	eventMap.erase(eventID);
	delete (&eventTmp);

	return;
}
