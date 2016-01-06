#pragma once
#include "hitBorder.h"
#include <vector>

class hitTree :
	public hitBorder
{
	public:
		hitTree();
		virtual ~hitTree();

		hitBorder* hitBrd;
		std::vector<std::pair<hitTree*, bool>> child;
	private:
};

