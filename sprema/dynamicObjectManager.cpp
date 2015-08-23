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
}

void dynamicObjectManager::render()
{
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
