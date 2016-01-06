#pragma once

/*

dynamicObjectManager作为整个游戏的核心框架，应在此管理主要的游戏功能，和组成整个游戏的“dynamicObjects”。

初始化时应将列表中所有的dynamicObject加载进游戏；（这意味着dynamicObject应有load,save函数）
在每帧更新时应调用每个dynamicObject的update函数，并处理其相互作用，最后调用render函数进行绘制。
生物（包括玩家）也是dynamicObject的一员，它们可以对世界中的物件产生影响，应对其开放可直接获取dynamicObject指针的函数以便进行相关修改。这个指针应是一个有向碰撞体的第一个相交的目标。
	a)相交时注意检测tag，若tag不符合则跳过。
	b)dynamicObjectManager应开放给各dynamicObject一个创建新dynamicObject的方法。
	c)比如玩家拿着一个什么东西想放到地面上。首先键盘鼠标操作调用到player的相关函数，在相关函数中判断玩家是想将其放置在地面上；根据鼠标指向位置发射一条射线，通过直接获取指针的函数获得目标方向的dynamicObject
	  指针（tag: blockGroupOnly），再进行动态类型转换将其转换成blockGroup。至此，玩家已成功与想要放置物体的blockGroup取得联系，再将之前记录下的相交点输入blockGroup的坐标转换函数获得相关信息，放置物体。
处理相互作用时，首先要获取每个dynamicObject的出力标记列表。（outputForceList）
	a)每个dynamicObject都应有一个基本的包围盒作为自身的标记。这个包围盒被定义为hitBorder *baseBorder;
	b)当dynamicObject想要对外界造成影响时，它应向出力标记列表中注册向外界的影响模式。如一堆燃烧的火应注册一个锥形的加热场，具有对应的标量函数，以及微小的上升气流。
		b-1)特别地，对于blockGroup，每个出力都应先在blockGroup层级进行操作，然后原封不动的分发至各个受影响的block进行相关处理。而block不注册进dynamicObjectManager。
	c)当dynamicObject的baseBorder之间相撞时，dynamicObjectManager应处理碰撞，碰撞的力度将被计算出来（由dynamicObject自身）并分发至每个dynamicObject。如果同时产生碰撞的是2+个物体，产生的就是单纯的合力。
	d)dynamicObject的相关函数：
		virtual void attachForces(force &mForce); //受到力的作用
		virtual list<force>* getImpactForces(); //碰撞时的出力
		**为了产生反作用力，force类中应加入父级指针dynamicObject* sourceObject;

在游戏结束时，应调用内存中所有dynamicObject的saveFile函数进行保存。

*/

#include "dynamicObject.h"
#include <map>
#include <vector>

#define objManager dynamicObjectManager::getInstance()

class dynamicObjectManager
{
	public:
		static dynamicObjectManager* getInstance();

		void init();
		void update();
		void render();

		int addForce(force &srcForce);//添加一个持续性作用（如类似扇面火焰的技能），返回值为forceID。这个ID唯一对应了一个force，从而便于在移除时快速定位。
		bool removeForce(int forceKey);//移除一个持续性作用，返回值为是否找到该作用（是否成功移除）
		bool attachForceOnce(force &srcForce);//瞬间施加一个作用，只施加一次，完毕后立即移除（根本不会被加入map），适用于类似瞬间推动一类的场合。返回值为是否产生了作用。

		//******TEST FUNCTION******//
		void testStartDemoAlpha();
		//******TEST FUNCTION******//

	private:
		static dynamicObjectManager* m_pInstance;

		dynamicObjectManager();
		virtual ~dynamicObjectManager();

		class garbageColle
		{
			public:
				~garbageColle()
				{
					if (dynamicObjectManager::m_pInstance)
						delete dynamicObjectManager::m_pInstance;
				}
		};

		static garbageColle dynamicObjectManagerGarbageCollector;

		std::map<int, force&> forceMap;
		std::vector<dynamicObject*> objectList;//还未成熟的碰撞检测体系
};


