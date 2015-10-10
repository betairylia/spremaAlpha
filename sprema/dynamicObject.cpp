#include "dynamicObject.h"



dynamicObject::dynamicObject()
{
}


dynamicObject::~dynamicObject()
{
}

bool dynamicObject::getHit(dynamicObject * target)
{
	return hitTarget->onHit(target->hitTarget);
}

bool dynamicObject::getHit(force * target)
{
	return hitTarget->onHit(target->hitBrd);
}

bool dynamicObject::getHit(hitBorder * target)
{
	return hitTarget->onHit(target);
}
