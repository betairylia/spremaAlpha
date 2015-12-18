#pragma once
#include "block.h"
#include "hitQuad.h"
#include "spremaMath.h"

using namespace spremaMath;

class testdemo_grassBlock :
	public block
{
	public:
		testdemo_grassBlock();
		virtual ~testdemo_grassBlock();

		virtual void attachForces(force &mForce) {};
		
		virtual list<force>* getImpactForces() 
		{
			force* result = new force(this, 
				[](hitBorder* integralBorder) -> Vector3
				{
					hitQuad boxQuad;
					//��integralBorder�任����ϵ
					//ȷ�����������ޣ���֮��
					//�ҡҡ�(0,mv,0)dxdydz���ھֲ�����ϵ�£�y������ײ�淨�򣻶��ڲݷ���m = 15��
					//return XXX;
					//TODO
				});
		};

		virtual void onJoin(blockGroup& group);//�����鱻���뷽����ʱ��������ע���¼���
		virtual void onLeave(blockGroup& group);//������ӷ�����������ʱ��������ע���¼���
};

