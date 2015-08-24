#pragma once

#include <cmath>

class block;

/*
	spremaEvent
	
	 ������¼����Ĳ��볡�����£�
		1)	��dynamicObject���������ƽ�����������������ħ��Դ�ȡ�
		2)	���������滻����ֲ��������ȡ�����Щ�ܸо�������ħ���������������Ӱ�������������1�����÷�ʽ������
			��ľ������
				���ǲ�������->��ľ�ķ�ʽ����ľ���Խ����ٳ���ǰ�����ܵ���������ħ������...��
	
	���Ծ�Ū1)�ͺ��ˡ�
	spremaEvent�Ǵ���update()��������һ�ε���ʱ�������һЩ�ж�һ��Ķ����������force���ࡣ

	����spremaEvent�������ڵ���block���ڵģ�����������ȴһ��������blockGroup���������������緶Χ��dynamicObjectManager����
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

