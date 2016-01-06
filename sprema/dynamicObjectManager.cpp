#include "dynamicObjectManager.h"

dynamicObjectManager* dynamicObjectManager::m_pInstance;

dynamicObjectManager * dynamicObjectManager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new dynamicObjectManager();
	}
	return m_pInstance;
}

void dynamicObjectManager::init()
{
}

void dynamicObjectManager::update()
{
	/*��ײ��⼰��������ѧ��ײ*/
	//Ŀǰ������Ͷ˵ķ�����֮���ٸİ�[O(N^2)]
	for each(auto object in objectList)
	{
		for each(auto target in objectList)
		{
			if (object->hitTarget->onHit(target->hitTarget))//��ɸ�Ȳ�����hitTree�ڲ�����
			{
				list<force>* objA = object->getImpactForces();
				list<force>* objB = object->getImpactForces();

				for each(auto forc in (*objA))
					target->attachForces(forc);

				for each(auto forc in (*objB))
					object->attachForces(forc);
			}
		}
	}

	/*force���*/
	for each(auto forc in forceMap)
	{
		for each(auto target in objectList)
		{
			if (forc.second.hitBrd->onHit(target->hitTarget))//��ɸ�Ȳ�����hitTree�ڲ�����
			{
				target->attachForces(forc.second);
			}
		}
	}
}

void dynamicObjectManager::render()
{
}

int dynamicObjectManager::addForce(force & srcForce)
{
	return 0;
}

bool dynamicObjectManager::removeForce(int forceKey)
{
	return false;
}

bool dynamicObjectManager::attachForceOnce(force & srcForce)
{
	return false;
}

void dynamicObjectManager::testStartDemoAlpha()
{
}

dynamicObjectManager::dynamicObjectManager()
{
}


dynamicObjectManager::~dynamicObjectManager()
{
}
