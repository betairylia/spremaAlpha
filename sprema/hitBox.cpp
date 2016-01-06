#include "hitBox.h"
#include "hitLine.h"
#include "hitPoint.h"
#include "hitSphere.h"
#include "hitTree.h"


hitBox::hitBox()
{
}


hitBox::~hitBox()
{
}

bool hitBox::onHit(hitBorder * target)
{
	switch (target->hitType)
	{
		case HIT_BOX:
		{
			hitBox* tarBox = dynamic_cast<hitBox*>(target);

			//����OBB�������Χ�У�����ϸ��Ϣ������...��û����0 0
			int i, j, countAxis = 0;
			Vector3 tmpAxis;
			double min1, min2, max1, max2;

			//��OBB��������ֱ��
			for (i = 0;i < 3;i++)
			{
				getProjection(Q * axes[i], min1, max1);
				tarBox->getProjection(Q * axes[i], min2, max2);
				if (max1 < min2 || max2 < min1) return false;
			}

			//�ж�OBB��������ֱ��
			for (i = 0;i < 3;i++)
			{
				getProjection(tarBox->Q * axes[i], min1, max1);
				tarBox->getProjection(tarBox->Q * axes[i], min2, max2);
				if (max1 < min2 || max2 < min1) return false;
			}

			//�������ᴹֱ�ľŸ���
			for (i = 0;i < 3;i++)
			{
				for (j = 0;j < 3;j++)
				{
					tmpAxis = (Q * axes[i]).crossProduct(tarBox->Q * axes[j]);//crossProduct: ���
					getProjection(tmpAxis, min1, max1);
					tarBox->getProjection(tmpAxis, min2, max2);
					if (max1 < min2 || max2 < min1) return false;
				}
			}

			return true;
		}
		break;

		case HIT_TREE:
		{
			hitTree* tarTree = dynamic_cast<hitTree*>(target);
			bool flag = false;

			if (onHit(tarTree->hitBrd))
			{
				if (tarTree->child.size() > 0)
				{
					for (auto iter = tarTree->child.begin(); iter != tarTree->child.end(); iter++)
					{
						iter->second = false;
						if (onHit(iter->first))
						{
							iter->second = true;
							flag = true;
						}
					}
					return flag;
				}
				else
				{
					return true;
				}
			}

			return false;
		}
		break;
	}
}

void hitBox::getProjection(Vector3 axis, double & min, double & max)
{
	int i;
	double value;
	min = max = axis.dotProduct(points[0]);//dotProduct: ���
	for (i = 1;i<8;i++)
	{
		value = axis.dotProduct(points[i]);
		if (min > value) min = value;
		if (max < value) max = value;
	}
	return;
}
