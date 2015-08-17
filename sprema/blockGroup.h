#pragma once

#include "dynamicObject.h"
#include "blockGroupStorage.h"

#include <map>

class blockGroup :
	public dynamicObject
{
	public:
		blockGroup();
		virtual ~blockGroup();

		//�̳���dynamicObject
		virtual void update();
		virtual void render(/*...*/);
		virtual void attachForces(list<force> &forces);
		virtual void loadFile(/*...*/);//���ļ��ж�ȡ���ݡ���mapBlockGroup�б����أ���չΪ����ʵʱ���ɵĵ��Ρ�
		virtual void saveFile(/*...*/);//���ļ��б������ݡ�

		//blockGroup
		void setBlock(int x, int y, int z, block &targetBlock);//���Խ���С��ģ�ķ����滻�����ģ���滻��Ϊ���ࣺ��һΪ�ܵ�������ò����Ĵ��ģ�滻���������������������в��������Ϊ��������ʱ�Ĵ��ģ�滻�����죩��������Ҫ�������һ��TerrainGenerator�ϡ�
	private:
		std::map<int, blockGroupStorage*> storeMap;
};

