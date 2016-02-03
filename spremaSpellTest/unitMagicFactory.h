#pragma once
#include "unitMagic.h"

class unitMagicFactory
{
	public:
		unitMagicFactory();
		~unitMagicFactory();

		static unitMagicFactory* magicFactory;
		static unitMagicFactory* getInstance();

		unitMagic* createMagicFromFactory(int ID)
		{
			return new tmpMagic();
		}
};

