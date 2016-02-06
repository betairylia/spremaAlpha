#pragma once

#include "unitMagic.h"
#include "controlHandle.h"

//����ӽ����ʽħ�������̿��ƺ������ĵ�һ��������Զ�ǵ�ǰ��С�ںţ��кţ�
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
		simpleLoop_Magic_testS0() { paramCount = 3; level = 0; }; //��Ȼ����Ĳ�����3������ʵ����Ҫ����Ĳ�����4��������ǰ��С�ںţ�
		~simpleLoop_Magic_testS0() {};

		virtual spellVariable* doMagic()
		{
			return nullptr;
		}

		//4��������1����ǰС�ںţ�2��ѭ��������3��ѭ��С�ڳ��ȣ�4��ѭ��������
		virtual controlHandle* doControl()
		{
			simpleLoop_testS0* tmp = new simpleLoop_testS0();
			tmp->init(paramList[0]->number[0], paramList[2]->number[0], paramList[1]->number[0], paramList[3]);
			return tmp;
		}
};