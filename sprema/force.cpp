#include "force.h"



template<typename Method>
force::force(dynamicObject * src, Method mth) :
	sourceObject(src),
	getValue(mth),
	factor(1.00)
{

}

force::~force()
{

}
