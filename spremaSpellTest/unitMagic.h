#pragma once

#include <iostream>
#include "spellVariable.h"

using namespace std;

class unitMagic
{
	public:
		unitMagic() : canControl(false) {}
		~unitMagic() {}

		virtual spellVariable* doMagic() = 0;
		void cleanParams()
		{
			int i;
			for (i = 0; i < paramList.size(); i++)
			{
				if (paramList.at(i)->temp)
				{
					delete paramList.at(i);
					paramList.erase(paramList.begin() + i);
					i--;
				}
			}
		}

		int paramCount;
		int level;//0: No Level; 1:F 2:E 3:D 4:C 5:B 6:A- 7:A 8:A+ 9:S 10:SS 11:SS+ 12:SS++ 13:EX
		bool canControl;

		vector<spellVariable*> paramList;
};

//在指定地点释放一个火球
class simpleFireBall_testS1 : public unitMagic
{
	public:
		simpleFireBall_testS1() : unitMagic() { paramCount = 1; level = 0; }
		~simpleFireBall_testS1() {}

		virtual spellVariable* doMagic()
		{
			if (paramList.size() < 1) return nullptr;

			spellVariable* v = new spellVariable();
			v->type = 'd';
			v->dyna.push_back(new dynamicObject("A fire ball"));

			cout << "Fire! at [" << paramList[0]->number.at(0) << ", " << paramList[0]->number.at(1) << ", " << paramList[0]->number.at(2) << "]" << endl;

			cleanParams();
			return v;
		}
};

//简单的取整函数，对应数字型（序列）。
class floor_testS2 : public unitMagic
{
	public:
		floor_testS2() : unitMagic() { paramCount = 1; level = 0; }
		~floor_testS2() {}

		virtual spellVariable* doMagic()
		{
			if (paramList.size() < 1) return nullptr;

			spellVariable* v = new spellVariable();
			v->type = 'n';

			int i, len = paramList[0]->number.size();
			
			for (i = 0;i < len;i++)
			{
				v->number.push_back((int)paramList[0]->number[i]);
			}

			cleanParams();
			return v;
		}
};