#pragma once

#include "force.h"
#include <list>

using namespace std;

class dynamicObject
{
	public:
		dynamicObject();
		virtual ~dynamicObject();
		
		virtual void attachForces(force &mForce) = 0;
		virtual list<force>* getImpactForces() = 0;

		virtual void update() = 0;

		virtual void loadFile(/*...*/) = 0;//从文件中读取数据。
		virtual void saveFile(/*...*/) = 0;//向文件中保存数据。

		hitBorder* hitTarget;//碰撞体，对于方块组：层级结构：方块组->存储器->方块

		/*virtual bool getHit(dynamicObject* target);
		virtual bool getHit(force* target);
		virtual bool getHit(hitBorder* target);*/
	protected:
		
};

