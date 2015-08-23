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
};

