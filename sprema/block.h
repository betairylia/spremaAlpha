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

	private:
		blockGroup* fatherGroup;
		std::string blockStr;
};

