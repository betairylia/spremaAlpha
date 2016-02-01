#include "spellAnalyser.h"

spellAnalyser::spellAnalyser()
{
}

spellAnalyser::~spellAnalyser()
{
}

bool spellAnalyser::doSpell(string spellStr)
{
	int i,len = spellStr.length();
	double tmp = 0;

	for (i = 0; i < len; i++)
	{
		switch (spellStr[i])
		{
			case 'v': //Variables
				i = readANum(spellStr, i + 1, tmp);
				//create variable object, add into map & stack
			break;

			case 's': //unitMagic
				i = readANum(spellStr, i + 1, tmp);
				//create magic object, check & save variable stack top, add into stack
			break;

			case '_': //build an matrix
				//create magic object, check & save variable stack top, add into stack
			break;

			case ';':
			break;

			case '(':
			break;

			case ')':
			break;

			case '+':
			break;

			case '-':
			break;

			case '*':
			break;

			case '/':
			break;

			case '%':
			break;

			case '=':
			break;
		}
	}

	return false;
}

int spellAnalyser::readANum(string spellStr, int startPos, double& outputValue)
{
	int i = 0, len = spellStr.length(), flag = 0, demi = 0;
	double ans = 0;

	for (i = startPos; i < len; i++)
	{
		switch (spellStr[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if(demi)
					ans += pow(0.1, (i - demi)) * (double)(spellStr[i] - '0');
				else
					ans += spellStr[i] - '0';
			break;

			case '.':
				demi = i;
				ans /= 10;
			break;

			default:
				flag = 1;
			break;
		}

		if (!demi) ans *= 10;
		if (flag) break;
	}

	outputValue = ans;
	return i - 1;
}
