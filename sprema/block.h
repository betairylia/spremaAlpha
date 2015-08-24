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

		//"�а���ȡ"��
		virtual void attachForces(force &mForce) {};
		virtual list<force>* getImpactForces() {};

		virtual void update() {};//���鱻�������������������Ҫ��blockGroup����ȡһЩ��Ϣ��

		virtual void loadFile() {};//block��һ��û�д洢/��ȡ������
		virtual void saveFile() {};

		virtual void onJoin(blockGroup& group);//�����鱻���뷽����ʱ��������ע���¼���
		virtual void onLeave(blockGroup& group);//������ӷ�����������ʱ��������ע���¼���

	private:
		blockGroup* fatherGroup;
		std::string blockStr;
};

