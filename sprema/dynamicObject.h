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

		virtual void loadFile(/*...*/) = 0;//���ļ��ж�ȡ���ݡ�
		virtual void saveFile(/*...*/) = 0;//���ļ��б������ݡ�

		hitBorder* hitTarget;//��ײ�壬���ڷ����飺�㼶�ṹ��������->�洢��->����

		/*virtual bool getHit(dynamicObject* target);
		virtual bool getHit(force* target);
		virtual bool getHit(hitBorder* target);*/
	protected:
		
};

