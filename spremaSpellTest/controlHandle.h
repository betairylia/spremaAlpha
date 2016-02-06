#pragma once

#include "spellVariable.h"

/*
可能会有的情况：

分支（if-else-elseif etc.）
循环（for-while-do etc.）
异形循环（或某种循环和分支的组合）

需要：
提供一个方法控制流程，在spellAnalyser每次处理循环i+1之前调用该方法控制执行流程，返回接下来要执行的小节。
输入参数可能有变量表（variableMap），当前小节序号。
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

		//nowBarIndex: 现在进行完的小节序号
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
