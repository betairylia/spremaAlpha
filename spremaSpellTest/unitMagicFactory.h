#pragma once

#include "controlMagic.h"
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
			switch (ID)
			{
				case 0:
					return new simpleLoop_Magic_testS0();
				break;

				case 1:
					return new simpleFireBall_testS1();
				break;

				case 2:
					return new floor_testS2();
				break;
			}
		}
};

