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

		block* setBlock(int x, int y, int z, const block& blockData);//���÷��顣��������滻�����ر��滻���ķ��飬���򷵻�nullptr��
};

