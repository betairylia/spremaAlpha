#pragma once
#include "hitBorder.h"

#include "spremaMath.h"

using namespace spremaMath;

class hitBox :
	public hitBorder
{
	public:
		hitBox();
		virtual ~hitBox();

		virtual bool onHit(hitBorder *target);
		bool facexXyYzZ[6];//x -x y -y z -z
		//virtual void switchSpace(/*todo*/) = 0;
		//virtual hitAABB getAABB() = 0;
	private:
		void getProjection(Vector3 axis, double &min, double &max);

		Vector3 points[8];
		Vector3 axes[3];
		Quaternion Q;
		Vector3 Npos;
};

