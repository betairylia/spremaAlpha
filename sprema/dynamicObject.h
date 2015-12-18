#pragma once

#include "spremaMath.h"
#include "force.h"
#include <list>

using namespace std;
using namespace spremaMath;

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

		virtual Vector3 getSpeed(Vector3 localPos = Vector3(0, 0, 0));

	protected:
		Vector3 speed;
};

