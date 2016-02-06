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
	int level;
}operationWTypes;


//�ļ���Ӧ���������ܸ����Ա���vector����ʱ�������ڴ��ַ�仯�����һϵ���鷳��
class spellAnalyser
{
	public:
		spellAnalyser();
		~spellAnalyser();

		bool doSpell(string spellStr);
		bool doOperation(string spellStr, operationWTypes & op, int barNum);
		int readANum(string spellStr, int startPos, double& outputValue);
		int readConst(string spellStr, int startPos, spellVariable*& outputValue);

		string readSpellFromFile(string fileDir)
		{
			int variableCount;
			string tmp;
			ifstream file;
			file.open(fileDir, ios::in);
			
			file >> variableCount;
			variableMap.resize(variableCount);

			file >> tmp;

			file.close();


			return tmp;
		}

		inline int getLevel(char op)
		{
			switch (op)
			{
				case '(':
					return 6;
				break;
				
				case ')':
				case ';':
				case ',':
					return 1;
				break;

				case '=':
					return 2;
				break;

				case '+':
				case '-':
					return 3;
				break;

				case '*':
				case '/':
				case '%':
					return 4;
				break;

				case '_':
				case 's':
					return 5;
				break;
			}
		}

	private:
		stack<operationWTypes> operationStack;
		stack<spellVariable*> paramStack;
		stack<controlHandle*> ctrlStack;
		vector<spellVariable> variableMap;
		
		//��NС�ڵ���ʼ���Ӧ��barPosCache[N-1].
		vector<int> barPosCache;
		//PSO

		unitMagicFactory * magicFactory;
};

