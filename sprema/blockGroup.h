#pragma once

#include "dynamicObject.h"
#include "renderable.h"
#include "blockGroupStorage.h"
#include "spremaEvent.h"
#include "hitBorder.h"

#include <map>

class blockGroup :
	public dynamicObject,
	public renderable
{
	public:
		blockGroup();
		virtual ~blockGroup();

		//继承自dynamicObject
		virtual void update();
		virtual void render(/*...*/);
		virtual void attachForces(list<force> &forces);
		virtual list<force>* getImpactForces();
		virtual void loadFile(/*...*/);//从文件中读取数据。在mapBlockGroup中被重载，扩展为可以实时生成的地形。
		virtual void saveFile(/*...*/);//向文件中保存数据。

		//blockGroup
		block* setBlock(int x, int y, int z, block &targetBlock);//用以进行小规模的方块替换。大规模的替换分为两类：其一为受到外界作用产生的大规模替换，这里用受力过程来进行操作。其二为生成世界时的大规模替换（创造），这里需要将其绑定至一个TerrainGenerator上。
	
		//注册事件相关
		double addMass(double amount);//返回操作后的质量
		void addEvent(spremaEvent &event);

		//注销事件相关
		double removeMass(double amount);//返回操作后的质量
		void removeEvent(spremaEvent &event);

	private:
		std::map<int, blockGroupStorage*> storeMap;

		double mass;//方块组总质量
		hitBorder* borderTree;//碰撞体，层级结构：方块组->存储器->方块
};

