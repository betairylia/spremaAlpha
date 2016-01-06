#pragma once

/*

dynamicObjectManager��Ϊ������Ϸ�ĺ��Ŀ�ܣ�Ӧ�ڴ˹�����Ҫ����Ϸ���ܣ������������Ϸ�ġ�dynamicObjects����

��ʼ��ʱӦ���б������е�dynamicObject���ؽ���Ϸ��������ζ��dynamicObjectӦ��load,save������
��ÿ֡����ʱӦ����ÿ��dynamicObject��update���������������໥���ã�������render�������л��ơ�
���������ң�Ҳ��dynamicObject��һԱ�����ǿ��Զ������е��������Ӱ�죬Ӧ���俪�ſ�ֱ�ӻ�ȡdynamicObjectָ��ĺ����Ա��������޸ġ����ָ��Ӧ��һ��������ײ��ĵ�һ���ཻ��Ŀ�ꡣ
	a)�ཻʱע����tag����tag��������������
	b)dynamicObjectManagerӦ���Ÿ���dynamicObjectһ��������dynamicObject�ķ�����
	c)�����������һ��ʲô������ŵ������ϡ����ȼ������������õ�player����غ���������غ������ж�������뽫������ڵ����ϣ��������ָ��λ�÷���һ�����ߣ�ͨ��ֱ�ӻ�ȡָ��ĺ������Ŀ�귽���dynamicObject
	  ָ�루tag: blockGroupOnly�����ٽ��ж�̬����ת������ת����blockGroup�����ˣ�����ѳɹ�����Ҫ���������blockGroupȡ����ϵ���ٽ�֮ǰ��¼�µ��ཻ������blockGroup������ת��������������Ϣ���������塣
�����໥����ʱ������Ҫ��ȡÿ��dynamicObject�ĳ�������б���outputForceList��
	a)ÿ��dynamicObject��Ӧ��һ�������İ�Χ����Ϊ����ı�ǡ������Χ�б�����ΪhitBorder *baseBorder;
	b)��dynamicObject��Ҫ��������Ӱ��ʱ����Ӧ���������б���ע��������Ӱ��ģʽ����һ��ȼ�յĻ�Ӧע��һ��׶�εļ��ȳ������ж�Ӧ�ı����������Լ�΢С������������
		b-1)�ر�أ�����blockGroup��ÿ��������Ӧ����blockGroup�㼶���в�����Ȼ��ԭ�ⲻ���ķַ���������Ӱ���block������ش�����block��ע���dynamicObjectManager��
	c)��dynamicObject��baseBorder֮����ײʱ��dynamicObjectManagerӦ������ײ����ײ�����Ƚ��������������dynamicObject�������ַ���ÿ��dynamicObject�����ͬʱ������ײ����2+�����壬�����ľ��ǵ����ĺ�����
	d)dynamicObject����غ�����
		virtual void attachForces(force &mForce); //�ܵ���������
		virtual list<force>* getImpactForces(); //��ײʱ�ĳ���
		**Ϊ�˲�������������force����Ӧ���븸��ָ��dynamicObject* sourceObject;

����Ϸ����ʱ��Ӧ�����ڴ�������dynamicObject��saveFile�������б��档

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

		int addForce(force &srcForce);//���һ�����������ã��������������ļ��ܣ�������ֵΪforceID�����IDΨһ��Ӧ��һ��force���Ӷ��������Ƴ�ʱ���ٶ�λ��
		bool removeForce(int forceKey);//�Ƴ�һ�����������ã�����ֵΪ�Ƿ��ҵ������ã��Ƿ�ɹ��Ƴ���
		bool attachForceOnce(force &srcForce);//˲��ʩ��һ�����ã�ֻʩ��һ�Σ���Ϻ������Ƴ����������ᱻ����map��������������˲���ƶ�һ��ĳ��ϡ�����ֵΪ�Ƿ���������á�

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
		std::vector<dynamicObject*> objectList;//��δ�������ײ�����ϵ
};


