#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include "unitMagic.h"
#include "controlMagic.h"
#include "controlHandle.h"
#include "spellVariable.h"
#include "unitMagicFactory.h"

using namespace std;

typedef struct _operationWTypes
{
	char type;//'_': create Matrix; '+' '-' '*' '/'...etc.; 's' for spells(unit Magic);
	unitMagic* magicPtr;
}operationWTypes;

class spellAnalyser
{
	public:
		spellAnalyser();
		~spellAnalyser();

		bool doSpell(string spellStr);
		int readANum(string spellStr, int startPos, double& outputValue);

		string readSpellFromFile(string fileDir)
		{
			string tmp;
			ifstream file;
			file.open(fileDir, ios::in);
			
			file >> tmp;

			file.close();
			return tmp;
		}

	private:
		stack<operationWTypes> operationStack;
		stack<spellVariable*> paramStack;
		stack<controlHandle*> ctrlStack;
		vector<spellVariable> variableMap;
		//PSO

		unitMagicFactory * magicFactory;
};

