#pragma once

#include "spellVariable.h"

class unitMagic
{
	public:
		unitMagic();
		~unitMagic();

		virtual spellVariable doMagic() = 0;
		int level = 0;//0: No Level; 1:F 2:E 3:D 4:C 5:B 6:A- 7:A 8:A+ 9:S 10:SS 11:SS+ 12:SS++ 13:EX
};
