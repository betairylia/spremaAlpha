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

		//�̳���dynamicObject
		virtual void update();
		virtual void render(/*...*/);
		virtual void attachForces(list<force> &forces);
		virtual list<force>* getImpactForces();
		virtual void loadFile(/*...*/);//���ļ��ж�ȡ���ݡ���mapBlockGroup�б����أ���չΪ����ʵʱ���ɵĵ��Ρ�
		virtual void saveFile(/*...*/);//���ļ��б������ݡ�

		//blockGroup
		block* setBlock(int x, int y, int z, block &targetBlock);//���Խ���С��ģ�ķ����滻�����ģ���滻��Ϊ���ࣺ��һΪ�ܵ�������ò����Ĵ��ģ�滻���������������������в��������Ϊ��������ʱ�Ĵ��ģ�滻�����죩��������Ҫ�������һ��TerrainGenerator�ϡ�
	
		//ע���¼����
		double addMass(double amount);//���ز����������
		void addEvent(spremaEvent &event);

		//ע���¼����
		double removeMass(double amount);//���ز����������
		void removeEvent(spremaEvent &event);

	private:
		std::map<int, blockGroupStorage*> storeMap;

		double mass;//������������
		hitBorder* borderTree;//��ײ�壬�㼶�ṹ��������->�洢��->����
};

