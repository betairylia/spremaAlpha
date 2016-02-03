#pragma once
#include <vector>

using namespace std;

//dynamicObject: for testing only.
class dynamicObject
{
	public:
		dynamicObject()
		{

		}

		dynamicObject(string s) : data(s)
		{

		}

		~dynamicObject()
		{

		}

		string data;
};
//<------------------------------>

class spellVariable
{
	public:
		spellVariable();
		~spellVariable();

		char type;//'d': dynamicObject; '('')'',': signs; 'n':number; NOTE: a single dynamicObject/number is a array that length = 1.
		
		vector<dynamicObject*> dyna;
		vector<double> number;

		bool temp;
};

