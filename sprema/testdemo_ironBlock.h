#pragma once
#include "block.h"
class testdemo_ironBlock :
	public block
{
	public:
		testdemo_ironBlock();
		~testdemo_ironBlock();

		virtual void onJoin(blockGroup& group);//�����鱻���뷽����ʱ��������ע���¼���
		virtual void onLeave(blockGroup& group);//������ӷ�����������ʱ��������ע���¼���
};

