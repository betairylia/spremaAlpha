#pragma once
#include "dynamicObject.h"
#include <string>

class blockGroup;

class block :
	public dynamicObject
{
	public:
		block();
		virtual ~block();

		//"有爱自取"。
		virtual void attachForces(force &mForce) {};
		virtual list<force>* getImpactForces() {};

		virtual void update() {};//方块被命令更新自身。它或许需要从blockGroup中提取一些信息。

		virtual void loadFile() {};//block类一般没有存储/读取函数。
		virtual void saveFile() {};

		virtual void onJoin(blockGroup& group);//当方块被加入方块组时，向其中注册事件。
		virtual void onLeave(blockGroup& group);//当方块从方块组中脱离时，从其中注销事件。

	private:
		blockGroup* fatherGroup;
		std::string blockStr;
};

