#pragma once

#include <cmath>

class block;

/*
	spremaEvent
	
	 这个“事件”的参与场合如下：
		1)	与dynamicObject互动，如推进器、电力发生器、魔力源等。
		2)	发生方块替换，如植物的生长等。（这些总感觉可以用魔力的流动对世界的影响代替掉（即变回1的作用方式））：
			树木生长：
				还是采用树苗->树木的方式，树木可以接着再长大，前提是受到了足量的魔力输入...？
	
	所以就弄1)就好了。
	spremaEvent是带有update()函数，在一段倒计时过后根据一些判定一类的东西对外产生force的类。

	由于spremaEvent是依附于单个block存在的，而其作用域却一般在整个blockGroup，甚至于整个世界范围（dynamicObjectManager）。
*/

class spremaEvent
{
	public:
		spremaEvent(block* srcBlock);
		virtual ~spremaEvent();

		virtual void update(float dt);
		virtual void onTimer() = 0;

	private:
		block* sourceBlock;
		float timeRemaining, timeRemainingMin, timeRemainingMax;
};

