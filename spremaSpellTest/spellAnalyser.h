#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include "unitMagic.h"
#include "loopMagic.h"
#include "spellVariable.h"

using namespace std;

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
		stack<unitMagic*> magicStack;
		stack<spellVariable> paramStack;
		stack<loopMagic*> loopStack;
		vector<spellVariable> variableMap;
		//PSO
};

