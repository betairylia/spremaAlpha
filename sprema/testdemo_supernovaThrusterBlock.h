#pragma once
#include "block.h"
class testdemo_supernovaThrusterBlock :
	public block
{
	public:
		testdemo_supernovaThrusterBlock();
		virtual ~testdemo_supernovaThrusterBlock();

		virtual void onJoin(blockGroup& group);//�����鱻���뷽����ʱ��������ע���¼���
		virtual void onLeave(blockGroup& group);//������ӷ�����������ʱ��������ע���¼���

	private:
		int eventID;
};

