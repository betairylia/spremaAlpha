#include "force.h"



template<typename Method>
force::force(dynamicObject * src, Method mth) :
	sourceObject(src),
	getValue(mth)
{
}

force::~force()
{
}
