#include "spellAnalyser.h"

spellAnalyser::spellAnalyser()
{
	magicFactory = unitMagicFactory::getInstance();
}

spellAnalyser::~spellAnalyser()
{
}

/*
doSpell() example:

v1=s1(df+_(v0%10,v0/10,0))

	dealed										operator							prarms
v1											|<									|<[v1]
v1=											|<[=]								|<[v1]
v1=s1										|<[s1][=]							|<[v1]
v1=s1(										|<[s1][=]							|<[(][v1]
v1=s1(df									|<[s1][=]							|<[df][(][v1]
v1=s1(df+									|<[+][s1][=]						|<[df][(][v1]
v1=s1(df+_									|<[_][+][s1][=]						|<[df][(][v1]
v1=s1(df+_(									|<[_][+][s1][=]						|<[(][df][(][v1]
v1=s1(df+_(v0								|<[_][+][s1][=]						|<[v0][(][df][(][v1]
v1=s1(df+_(v0%								|<[%][_][+][s1][=]					|<[v0][(][df][(][v1]
v1=s1(df+_(v0%10							|<[%][_][+][s1][=]					|<[10][v0][(][df][(][v1]
											|<[_][+][s1][=]						|<[v0%10][(][df][(][v1]
v1=s1(df+_(v0%10,							|<[_][+][s1][=]						|<[,][v0%10][(][df][(][v1]
v1=s1(df+_(v0%10,v0							|<[_][+][s1][=]						|<[v0][,][v0%10][(][df][(][v1]
v1=s1(df+_(v0%10,v0/						|<[/][_][+][s1][=]					|<[v0][,][v0%10][(][df][(][v1]
v1=s1(df+_(v0%10,v0/10						|<[/][_][+][s1][=]					|<[10][v0][,][v0%10][(][df][(][v1]
											|<[_][+][s1][=]						|<[v0/10][,][v0%10][(][df][(][v1]
v1=s1(df+_(v0%10,v0/10,						|<[_][+][s1][=]						|<[,][v0/10][,][v0%10][(][df][(][v1]
v1=s1(df+_(v0%10,v0/10,0					|<[_][+][s1][=]						|<[0][,][v0/10][,][v0%10][(][df][(][v1]
v1=s1(df+_(v0%10,v0/10,0)					|<[_][+][s1][=]						|<[)][0][,][v0/10][,][v0%10][(][df][(][v1]
											|<[+][s1][=]						|<[v0%10,v0/10,0][df][(][v1]
											|<[s1][=]							|<[df+v0%10,v0/10,0][(][v1]
v1=s1(df+_(v0%10,v0/10,0))					|<[s1][=]							|<[)][df+v0%10,v0/10,0][(][v1]
											|<[=]								|<[s1(df+v0%10,v0/10,0)][v1]
											|<									|<
Completed.

Test file:

File location:								root
File name:									testSpell-dircFlameArray.txt
File contains:								v0=s0(_(1%10,1/10,0));
*/
bool spellAnalyser::doSpell(string spellStr)
{
	while (paramStack.size()) paramStack.pop();
	while (operationStack.size()) operationStack.pop();
	while (ctrlStack.size()) ctrlStack.pop();
	variableMap.clear();

	int i,len = spellStr.length(), nowRowNum = 1;

	double tmp = 0;
	operationWTypes tmpOperator;

	bool ovrFlag;

	for (i = 0; i < len; i++)
	{
		switch (spellStr[i])
		{
			case 'v': //Variables
				i = readANum(spellStr, i + 1, tmp);
				
				//check if this variable is created already
				//or create it
				while (variableMap.size() <= tmp)
				{
					spellVariable a;
					variableMap.push_back(a);
				}

				//add into stack
				paramStack.push(&variableMap.at(tmp));
			break;

			case 's': //unitMagic
			{
				i = readANum(spellStr, i + 1, tmp);

				//create magic object, check & save variable stack top, add into stack
				tmpOperator.type = 's';
				tmpOperator.magicPtr = magicFactory->createMagicFromFactory(i);

				operationStack.push(tmpOperator);
			}
			break;

			case ';':
				while (paramStack.size()) paramStack.pop();
				while (operationStack.size()) operationStack.pop();
				nowRowNum++;
			break;

			case '(':
			case ')':
			case ',':
			{
				spellVariable* a = new spellVariable();
				a->temp = true;
				a->type = spellStr[i];

				paramStack.push(a);
			}
			break;

			case '_':
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '=':
				tmpOperator.type = spellStr[i];

				operationStack.push(tmpOperator);
			break;

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
			case '.':
			{
				spellVariable* a = new spellVariable();
				a->temp = true;
				i = readANum(spellStr, i, tmp);

				a->type = 'n';
				a->number.push_back(tmp);

				paramStack.push(a);
			}
			break;

			//todo: consts, df etc.
		}
		//check operator stack top:
		//	's'			=>				make spell
		//	's'[ctrl]	=>				make control (loop, code jump etc.)
		//	'+'	'-'...	=>				calculate
		//	'_'			=>				make array
		//then push into variable / controlHandle stack.

		ovrFlag = false;
		while (operationStack.size() && !ovrFlag)
		{
			switch (operationStack.top().type)
			{
				case 's':
				{
					if (paramStack.top()->type != ')')
					{
						ovrFlag = true;
						break;
					}

					spellVariable* t = paramStack.top();
					paramStack.pop();
					delete t;

					if (paramStack.size() < 1)
					{
						ovrFlag = true;
						break;
					}

					if (operationStack.top().magicPtr->canControl)
					{
						//todo: ctrl Magics.
					}
					else
					{
						unitMagic* uM = operationStack.top().magicPtr;

						//NO ERRORS THERE, cuz errors can be found during compling.
						while (paramStack.top()->type != '(')
						{
							if (paramStack.top()->type == ',')
							{
								spellVariable* t = paramStack.top();
								paramStack.pop();
								delete t;

								continue;
							}

							else if (paramStack.top()->type != ')')
							{
								uM->paramList.push_back(paramStack.top());
								paramStack.pop();
							}

							else
							{
								//throw error
								ovrFlag = true;
								break;
							}
						}
						if (paramStack.top()->type == '(')
						{
							spellVariable* t = paramStack.top();
							paramStack.pop();
							delete t;
						}

						spellVariable* returnValue = uM->doMagic();

						paramStack.push(returnValue);
						operationStack.pop();
					}
				}
				break;

				case '+':
				{
					if (paramStack.size() < 2)
					{
						ovrFlag = true;
						break;
					}

					spellVariable* tmp = paramStack.top();
					paramStack.pop();

					if (tmp->type == 'n' && paramStack.top()->type == 'n' && tmp->number.size() == paramStack.top()->number.size())
					{
						int j, tl = tmp->number.size();
						for (j = 0; j < tl; j++)
						{
							paramStack.top()->number.at(j) += tmp->number.at(j);
						}
						operationStack.pop();

						if (tmp->temp) delete tmp;
					}
					else
					{
						paramStack.push(tmp);
						ovrFlag = true;
						break;
					}
				}
				break;

				case '-':
				{
					if (paramStack.size() < 2)
					{
						ovrFlag = true;
						break;
					}

					spellVariable* tmp = paramStack.top();
					paramStack.pop();

					if (tmp->type == 'n' && paramStack.top()->type == 'n' && tmp->number.size() == paramStack.top()->number.size())
					{
						int j, tl = tmp->number.size();
						for (j = 0; j < tl; j++)
						{
							paramStack.top()->number.at(j) -= tmp->number.at(j);
						}
						operationStack.pop();

						if (tmp->temp) delete tmp;
					}
					else
					{
						paramStack.push(tmp);
						ovrFlag = true;
						break;
					}
				}
				break;

				case '*':
				{
					if (paramStack.size() < 2)
					{
						ovrFlag = true;
						break;
					}

					spellVariable* tmp = paramStack.top();
					paramStack.pop();

					if (tmp->type == 'n' && paramStack.top()->type == 'n' && tmp->number.size() == paramStack.top()->number.size())
					{
						int j, tl = tmp->number.size();
						for (j = 0; j < tl; j++)
						{
							paramStack.top()->number.at(j) *= tmp->number.at(j);
						}
						operationStack.pop();

						if (tmp->temp) delete tmp;
					}
					else
					{
						paramStack.push(tmp);
						ovrFlag = true;
						break;
					}
				}
				break;

				case '/':
				{
					if (paramStack.size() < 2)
					{
						ovrFlag = true;
						break;
					}

					spellVariable* tmp = paramStack.top();
					paramStack.pop();

					if (tmp->type == 'n' && paramStack.top()->type == 'n' && tmp->number.size() == paramStack.top()->number.size())
					{
						int j, tl = tmp->number.size();
						for (j = 0; j < tl; j++)
						{
							paramStack.top()->number.at(j) /= tmp->number.at(j);
						}
						operationStack.pop();

						if (tmp->temp) delete tmp;
					}
					else
					{
						paramStack.push(tmp);
						ovrFlag = true;
						break;
					}
				}
				break;

				case '%':
				{
					if (paramStack.size() < 2)
					{
						ovrFlag = true;
						break;
					}

					spellVariable* tmp = paramStack.top();
					paramStack.pop();

					if (tmp->type == 'n' && paramStack.top()->type == 'n' && tmp->number.size() == paramStack.top()->number.size())
					{
						int j, tl = tmp->number.size();
						for (j = 0; j < tl; j++)
						{
							paramStack.top()->number.at(j) = (double)((int)paramStack.top()->number.at(j) % (int)tmp->number.at(j));
						}
						operationStack.pop();

						if (tmp->temp) delete tmp;
					}
					else
					{
						paramStack.push(tmp);
						ovrFlag = true;
						break;
					}
				}
				break;

				case '=':
				{
					if (paramStack.size() < 2)
					{
						ovrFlag = true;
						break;
					}

					spellVariable* tmp = paramStack.top();
					paramStack.pop();

					if (tmp->type == 'n')
					{
						paramStack.top()->type = 'n';
						paramStack.top()->number.clear();

						int j, tl = tmp->number.size();
						for (j = 0; j < tl; j++)
						{
							paramStack.top()->number.push_back(tmp->number.at(j));
						}
						operationStack.pop();

						if (tmp->temp) delete tmp;
					}

					else if (tmp->type == 'd')
					{
						paramStack.top()->type = 'd';
						paramStack.top()->dyna.clear();

						int j, tl = tmp->dyna.size();
						for (j = 0; j < tl; j++)
						{
							paramStack.top()->dyna.push_back(tmp->dyna.at(j));
						}
						operationStack.pop();

						if (tmp->temp) delete tmp;
					}

					else
					{
						paramStack.push(tmp);
						ovrFlag = true;
						break;
					}
				}
				break;

				case '_':
				{
					if (paramStack.top()->type != ')')
					{
						ovrFlag = true;
						break;
					}

					spellVariable* t = paramStack.top();
					paramStack.pop();
					delete t;

					if (paramStack.size() < 1)
					{
						ovrFlag = true;
						break;
					}

					stack<spellVariable*> tmpStack;
					char typ = paramStack.top()->type;

					if (typ == ')' || typ == '(' || typ == ',')
					{
						ovrFlag = true;
						break;
					}

					while (paramStack.top()->type == typ || paramStack.top()->type == ',')
					{
						if (paramStack.top()->type == ',')
						{
							spellVariable* t = paramStack.top();
							paramStack.pop();
							delete t;

							continue;
						}

						tmpStack.push(paramStack.top());
						paramStack.pop();
					}

					if (paramStack.top()->type == '(')
					{
						paramStack.pop();
						paramStack.push(tmpStack.top());
						tmpStack.pop();

						while (tmpStack.size())
						{
							if (typ == 'n')
							{
								int j, tl = tmpStack.top()->number.size();
								for (j = 0; j < tl; j++)
								{
									paramStack.top()->number.push_back(tmpStack.top()->number[j]);
								}
							}

							if (typ == 'd')
							{
								int j, tl = tmpStack.top()->dyna.size();
								for (j = 0; j < tl; j++)
								{
									paramStack.top()->dyna.push_back(tmpStack.top()->dyna[j]);
								}
							}

							tmpStack.pop();
						}

						operationStack.pop();
					}
					else
					{
						//throw error
						ovrFlag = true;
						break;
					}
				}
				break;
			}
		}
	}

	cout << "Variable Table:" << endl;
	for (i = 0; i < variableMap.size(); i++)
	{
		cout << "v" << i << ":\t";
		
		if (variableMap[i].type == 'n')
		{
			cout << "Number\t" << "value = [";
			int j;
			for (j = 0; j < variableMap[i].number.size(); j++)
			{
				cout << variableMap[i].number[j];
				if (j + 1 < variableMap[i].number.size()) cout << ", ";
			}
			cout << "]" << endl;
		}

		if (variableMap[i].type == 'd')
		{
			cout << "dObject\t" << "value = [";
			int j;
			for (j = 0; j < variableMap[i].dyna.size(); j++)
			{
				cout << variableMap[i].dyna[j]->data;
				if (j + 1 < variableMap[i].dyna.size()) cout << ", ";
			}
			cout << "]" << endl;
		}
	}

	return true;
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
				{
					ans *= 10;
					ans += spellStr[i] - '0';
				}
			break;

			case '.':
				demi = i;
			break;

			default:
				flag = 1;
			break;
		}

		if (flag) break;
	}

	outputValue = ans;
	return i - 1;
}
