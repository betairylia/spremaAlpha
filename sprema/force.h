#pragma once

#include "hitBorder.h"
#include "spremaMath.h"
#include <functional>

enum forceType
{						//		名称					主要debuff						备注
	CUT = 0x1,			//		切断				 出血、残废、即死
	HIT = 0x2,			//		打击				 迷晕、眩晕、昏迷
	SPEAR = 0x4,		//		突刺				 刺痛、激痛、贯穿
	EXPLOSION = 0x8,	//		爆破					   击飞
	FIRE = 0x10,		//		火
	ICE = 0x20,			//		冰
	WATER = 0x40,		//		水
	THUNDER = 0x80,		//		雷
	WIND = 0x100,		//		风
	LIGHT = 0x200,		//		光
	DARK = 0x400,		//		暗
	NATURE = 0x800,		//		自然
	POWER = 0x1000,		//		纯粹
	REAL = 0x2000		//		真实伤害					无					纯粹的造成除特殊防护外的等额伤害，不会对地图产生任何影响。
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

