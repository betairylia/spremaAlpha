#pragma once

/*
�о�blockGroup�Ļ������ƺ�������Щ���⡣
�����blockGroup������ֱ�ӽ��в����Ļ��޷�����Ļ����΢�ۣ�������ÿ�����飩Ҫ�أ�
���Ƿַ���ȥ�Ļ����п��ܳ����ظ����㡣��������ֻ����forceType::HIT����λ�ư�ɶ�����߰���ģ�...

����һ����������ϵ�����һ�������ҵ������ϣ�
a)	��һ�µĳ����Ӧ���Ƕ����أ�
b)	����ҵ�������������Ӧ����ɶ����˺���

����	a)	���������������ɡ�
		b)	����Ǵ󴸵Ļ�����Ϊ��������������ɵ��˺���Ȼ���ӡ�����������ȵ�ǰ���£���ɵ��˺��ܶ�Ӧ����ȡ�ֻ���������˺�����ɢ�ڶ����λ�����ָ��˺��쳣�ĸ��ʻ��С��
			
			�����˺����ɢ�����о����������ʱ�򲻿ɱ����Ҫ������...���ܾ��ǵû��ְ�hhh
				���ɢ�������ַ�ʱֱ�Ӱ�force�ַ���ȥ��Ȼ��ÿ��΢Ԫ���������ײ��ȥ��ȡ������������ײ�о���ô���ֹ���ͼ�Σ������Ҫforce�Ǳ߼�һ�����֣��е���������̫����Ļ�...����

		ʣ�µ��ƺ�����һ������...�Ǿ�������������⣬ÿ��΢Ԫ����ֻ����һ���ֱ�¶���⣬ֻ����һ���ֲŻ��ܵ����á��ƺ�Ҫ�Ӹ���������...������ֻ��box�������Ӱ�죬���Ը�box�������ͺá�

		blockGroup�ڴ�����ײʱ��Ҫ�ر�Ĵ���ʽ��
			1��	�ҵ�һ�ַ����ܹ����ٶ�λ�����ܵ���ײ�ķ��顾��һ���ǹؼ�...��
			2��	�������ǵ�Ĭ����ײ������
			3��	����ײ������Ŀ�꣬ʩ�ӷ���������
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

		//�̳���dynamicObject
		virtual void update();
		virtual void render(/*...*/);
		virtual void attachForces(list<force> &forces);
		virtual list<force>* getImpactForces();//getImpactForces֮ǰ���������ײ���
		virtual void loadFile(/*...*/);//���ļ��ж�ȡ���ݡ���mapBlockGroup�б����أ���չΪ����ʵʱ���ɵĵ��Ρ�
		virtual void saveFile(/*...*/);//���ļ��б������ݡ�

		void getImpactForces_d(list<force>* listA, hitBorder* hit);

		//blockGroup
		block* setBlock(int x, int y, int z, block &targetBlock);//���Խ���С��ģ�ķ����滻�����ģ���滻��Ϊ���ࣺ��һΪ�ܵ�������ò����Ĵ��ģ�滻���������������������в��������Ϊ��������ʱ�Ĵ��ģ�滻�����죩��������Ҫ�������һ��TerrainGenerator�ϡ�
		void blockUpdateCompleted(/*�ʵ��Ĳ���*/);//��������һ��������������ΧһȦ����ĸ��¹�����

		//ע���¼����
		double addMass(double amount);//���ز����������
		int addEvent(spremaEvent &targetEvent);

		//ע���¼����
		double removeMass(double amount);//���ز����������
		void removeEvent(int eventID);

	private:
		std::map<int, blockGroupStorage*> storeMap;
		std::map<int, spremaEvent&> eventMap;

		double mass;//������������
};

