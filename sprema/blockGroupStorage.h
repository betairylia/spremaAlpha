#pragma once

#define CHUNK_SIZEX 16
#define CHUNK_SIZEY 16
#define CHUNK_SIZEZ	16

#include "block.h"

class blockGroupStorage
{
	public:
		blockGroupStorage();
		virtual ~blockGroupStorage();

		block* setBlock(int x, int y, int z, const block& blockData);//放置方块。如果发生替换，返回被替换掉的方块，否则返回nullptr。
};

