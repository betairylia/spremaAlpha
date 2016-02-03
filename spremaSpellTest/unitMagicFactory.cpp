#include "unitMagicFactory.h"

unitMagicFactory* unitMagicFactory::magicFactory = nullptr;

unitMagicFactory::unitMagicFactory()
{
}


unitMagicFactory::~unitMagicFactory()
{
}

unitMagicFactory * unitMagicFactory::getInstance()
{
	if (magicFactory == nullptr)
	{
		magicFactory = new unitMagicFactory();
	}

	return magicFactory;
}
