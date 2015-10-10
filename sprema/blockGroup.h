#pragma once

/*
感觉blockGroup的机制上似乎还是有些问题。
如果在blockGroup层面上直接进行操作的话无法避免的会忽略微观（下限是每个方块）要素；
但是分发下去的话又有可能出现重复计算。（现在先只考虑forceType::HIT，即位移啊啥的乱七八糟的）...

考虑一个情况。天上掉下来一个锤子砸到地面上，
a)	这一下的冲击力应该是多少呢？
b)	如果砸到了生物身上又应该造成多少伤害？

——	a)	单纯的遵守物理定律。
		b)	如果是大锤的话，因为质量增加所以造成的伤害当然增加。但在质量相等的前提下，造成的伤害总额应该相等。只不过由于伤害被分散于多个部位，出现高伤害异常的概率会减小。
			
			——伤害会分散。（感觉最后受力的时候不可避免的要积分了...可能就是得积分吧hhh
				会分散——即分发时直接把force分发出去，然后每个微元用自身的碰撞盒去获取受力。由于碰撞盒就那么几种规则图形，大概是要force那边加一个积分（有的力（场）太奇葩的话...）。

		剩下的似乎还有一个问题...那就是受力面的问题，每个微元可能只会有一部分暴露在外，只有这一部分才会受到作用。似乎要加个限制条件...？——只有box会受这个影响，所以给box单出来就好。

		blockGroup在处理碰撞时需要特别的处理方式：
			1）	找到一种方法能够快速定位所有受到碰撞的方块【这一步是关键...】
			2）	激活他们的默认碰撞出力。
			3）	找碰撞出力的目标，施加反作用力。
*/

#include "dynamicObject.h"
#include "renderable.h"
#include "blockGroupStorage.h"
#include "spremaEvent.h"
#include "hitBorder.h"

#include <map>
#include <cmath>

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
		virtual list<force>* getImpactForces();//getImpactForces之前必须进行碰撞检测
		virtual void loadFile(/*...*/);//从文件中读取数据。在mapBlockGroup中被重载，扩展为可以实时生成的地形。
		virtual void saveFile(/*...*/);//向文件中保存数据。

		void getImpactForces_d(list<force>* listA, hitBorder* hit);

		//blockGroup
		block* setBlock(int x, int y, int z, block &targetBlock);//用以进行小规模的方块替换。大规模的替换分为两类：其一为受到外界作用产生的大规模替换，这里用受力过程来进行操作。其二为生成世界时的大规模替换（创造），这里需要将其绑定至一个TerrainGenerator上。
		void blockUpdateCompleted(/*适当的参数*/);//用来处理一个方块更新完后周围一圈方块的更新工作。

		//注册事件相关
		double addMass(double amount);//返回操作后的质量
		int addEvent(spremaEvent &targetEvent);

		//注销事件相关
		double removeMass(double amount);//返回操作后的质量
		void removeEvent(int eventID);

	private:
		std::map<int, blockGroupStorage*> storeMap;
		std::map<int, spremaEvent&> eventMap;

		double mass;//方块组总质量
};

