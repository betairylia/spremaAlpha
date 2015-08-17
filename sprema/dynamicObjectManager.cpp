#include "dynamicObjectManager.h"



dynamicObjectManager * dynamicObjectManager::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new dynamicObjectManager();
	}
	return m_pInstance;
}

dynamicObjectManager::dynamicObjectManager()
{
}


dynamicObjectManager::~dynamicObjectManager()
{
}
