#pragma once

#include "unitMagic.h"
#include "controlHandle.h"

//对于咏唱构式魔法（流程控制函数）的第一个参数永远是当前的小节号（行号）
class controlMagic :
	public unitMagic
{
	public:
		controlMagic() { canControl = true; };
		~controlMagic();

		virtual spellVariable* doMagic() = 0;
		virtual controlHandle* doControl() = 0;
};

class simpleLoop_Magic_testS0 : public controlMagic
{
	public:
		simpleLoop_Magic_testS0() { paramCount = 3; level = 0; }; //虽然需求的参数是3个，但实际需要传入的参数有4个。（当前的小节号）
		~simpleLoop_Magic_testS0() {};

		virtual spellVariable* doMagic()
		{
			return nullptr;
		}

		//4个参数：1）当前小节号；2）循环次数；3）循环小节长度；4）循环计数器
		virtual controlHandle* doControl()
		{
			simpleLoop_testS0* tmp = new simpleLoop_testS0();
			tmp->init(paramList[0]->number[0], paramList[2]->number[0], paramList[1]->number[0], paramList[3]);
			return tmp;
		}
};