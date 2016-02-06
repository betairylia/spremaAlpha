#pragma once

#include "spellVariable.h"

/*
���ܻ��е������

��֧��if-else-elseif etc.��
ѭ����for-while-do etc.��
����ѭ������ĳ��ѭ���ͷ�֧����ϣ�

��Ҫ��
�ṩһ�������������̣���spellAnalyserÿ�δ���ѭ��i+1֮ǰ���ø÷�������ִ�����̣����ؽ�����Ҫִ�е�С�ڡ�
������������б�����variableMap������ǰС����š�
*/

class controlHandle
{
	public:
		controlHandle() { alive = true; };
		~controlHandle();

		virtual int control(vector<spellVariable>& variableMap, int nowBarIndex) = 0;
		bool alive;
};

class simpleLoop_testS0 : public controlHandle
{
	public:
		simpleLoop_testS0() {};
		~simpleLoop_testS0() {};

		int loopCount, loopBegin, loopEnd;
		spellVariable* counter;

		void init(int lBegin, int lDuring, int lCount, spellVariable* c)
		{
			loopCount = lCount;
			loopBegin = lBegin;
			loopEnd = lBegin + lDuring;
			counter = c;

			counter->type = 'n';
			counter->number.clear();
			counter->number.push_back(0);
		}

		//nowBarIndex: ���ڽ������С�����
		virtual int control(vector<spellVariable>& variableMap, int nowBarIndex)
		{
			if (nowBarIndex == loopEnd)
			{
				loopCount--;
				counter->number.at(0) = counter->number.at(0) + 1;

				if (loopCount)
					return loopBegin;

				alive = false;
				return nowBarIndex + 1;
			}
		}
};
