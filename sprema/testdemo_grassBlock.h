#pragma once
#include "block.h"
class testdemo_grassBlock :
	public block
{
	public:
		testdemo_grassBlock();
		virtual ~testdemo_grassBlock();

		virtual void onJoin(blockGroup& group);//�����鱻���뷽����ʱ��������ע���¼���
		virtual void onLeave(blockGroup& group);//������ӷ�����������ʱ��������ע���¼���
};

