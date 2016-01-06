#pragma once

#include "hitBorder.h"
#include "spremaMath.h"
#include <functional>

enum forceType
{						//		����					��Ҫdebuff						��ע
	CUT = 0x1,			//		�ж�				 ��Ѫ���зϡ�����
	HIT = 0x2,			//		���				 ���Ρ�ѣ�Ρ�����
	SPEAR = 0x4,		//		ͻ��				 ��ʹ����ʹ���ᴩ
	EXPLOSION = 0x8,	//		����					   ����
	FIRE = 0x10,		//		��
	ICE = 0x20,			//		��
	WATER = 0x40,		//		ˮ
	THUNDER = 0x80,		//		��
	WIND = 0x100,		//		��
	LIGHT = 0x200,		//		��
	DARK = 0x400,		//		��
	NATURE = 0x800,		//		��Ȼ
	POWER = 0x1000,		//		����
	REAL = 0x2000		//		��ʵ�˺�					��					�������ɳ����������ĵȶ��˺�������Ե�ͼ�����κ�Ӱ�졣
};

class dynamicObject;

class force
{
	public:

		template<typename Method>
		force(dynamicObject* src, Method mth);
		virtual ~force();

		hitBorder* hitBrd;
		std::function<spremaMath::Vector3(hitBorder* integralBorder)> getValue;

		double factor;
		double numberValue;
	private:
		dynamicObject* sourceObject;
};

