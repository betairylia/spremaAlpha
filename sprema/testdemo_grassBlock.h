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
					//给integralBorder变换坐标系
					//确定积分上下限，积之：
					//∫∫∫(0,mv,0)dxdydz（在局部坐标系下，y轴沿碰撞面法向；对于草方块m = 15）
					//return XXX;
					//TODO
				});
		};

		virtual void onJoin(blockGroup& group);//当方块被加入方块组时，向其中注册事件。
		virtual void onLeave(blockGroup& group);//当方块从方块组中脱离时，从其中注销事件。
};

