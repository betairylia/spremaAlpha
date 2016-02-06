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

	barPosCache.clear();
	barPosCache.push_back(0);

	int i,len = spellStr.length(), nowRowNum = 1, targetRowNum;

	double tmp = 0;
	operationWTypes tmpOperator;

	for (i = 0; i < len; i++)
	{
		switch (spellStr[i])
		{
			case 'u': //uniform Variables
			{
				spellVariable* tmp;

				i = readConst(spellStr, i + 1, tmp);
				paramStack.push(tmp);
			}
			break;

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
				tmpOperator.magicPtr = magicFactory->createMagicFromFactory(tmp);
				tmpOperator.level = getLevel('s');

				doOperation(spellStr, tmpOperator, nowRowNum);

				operationStack.push(tmpOperator);
			}
			break;

			case ';':
				tmpOperator.type = spellStr[i];
				tmpOperator.level = getLevel(spellStr[i]);

				doOperation(spellStr, tmpOperator, nowRowNum);

				while (paramStack.size()) paramStack.pop();
				while (operationStack.size()) operationStack.pop();

				//在这里插入咏唱构式（流程控制）
				while (ctrlStack.size() && ctrlStack.top()->alive == false) ctrlStack.pop();
				if (ctrlStack.size())
				{
					targetRowNum = ctrlStack.top()->control(variableMap, nowRowNum);
				}
				else
				{
					targetRowNum = nowRowNum + 1;
				}

				if (targetRowNum != nowRowNum + 1)
				{
					//可以跳转
					if (targetRowNum <= barPosCache.size())
					{
						//进行跳转
						i = barPosCache.at(targetRowNum - 1);
						nowRowNum = targetRowNum;
					}
					//不能跳转（没有那一小节的索引），向后寻找
					else
					{
						//todo
					}
				}
				else
				{
					//统计行号
					if (nowRowNum == barPosCache.size())
						barPosCache.push_back(i + 1);

					nowRowNum++;
				}
			break;

			case ',':
				tmpOperator.type = spellStr[i];
				tmpOperator.level = getLevel(spellStr[i]);

				doOperation(spellStr, tmpOperator, nowRowNum);
			break;

			case '_':
				i = readANum(spellStr, i + 1, tmp);

				//create magic object, check & save variable stack top, add into stack
				tmpOperator.type = '_';
				tmpOperator.magicPtr = (unitMagic*)(int)tmp;
				tmpOperator.level = getLevel('_');

				doOperation(spellStr, tmpOperator, nowRowNum);

				operationStack.push(tmpOperator);
			break;

			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '=':
			case '(':
			case ')':
				tmpOperator.type = spellStr[i];
				tmpOperator.level = getLevel(spellStr[i]);

				if(doOperation(spellStr, tmpOperator, nowRowNum))
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
		//v0=s0(uFP+_(1%10,1/10,0));v1=0;v1=v1+1;
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

bool spellAnalyser::doOperation(string spellStr, operationWTypes & op, int barNum)
{
	if (!operationStack.size()) return true;

	bool ovrFlag = false;

	while (operationStack.size() && operationStack.top().level >= op.level && !ovrFlag)
	{
		switch (operationStack.top().type)
		{
			case 's':
			{
				if (paramStack.size() < operationStack.top().magicPtr->paramCount)
				{
					ovrFlag = true;
					break;
				}

				if (paramStack.size() < 1)
				{
					ovrFlag = true;
					break;
				}

				if (operationStack.top().magicPtr->canControl)
				{
					controlMagic* uM = dynamic_cast<controlMagic*>(operationStack.top().magicPtr);
					int pC = 0;//pC: 当前已经传入了的参数的计数（paramCount）；数量符合要求时停止传入参数。
					int tC = operationStack.top().magicPtr->paramCount;
					uM->paramList.resize(tC + 1);

					//对于咏唱构式型先传入当前小节序号：
					spellVariable* nowNumTmpParam = new spellVariable();
					
					nowNumTmpParam->type = 'n';
					nowNumTmpParam->number.push_back(barNum);

					uM->paramList[0] = nowNumTmpParam;

					//NO ERRORS THERE, cuz errors can be found during compling.
					//参数不应出错。在编辑咒文（IDE中）时就会完全避免掉参数类型的错误。
					while (pC < tC)
					{
						uM->paramList[tC - pC] = paramStack.top();
						paramStack.pop();
						pC++;
					}

					spellVariable* returnValue = uM->doMagic();
					controlHandle* returnHandle = uM->doControl();

					if (returnValue)
						paramStack.push(returnValue);
					if (returnHandle)
						ctrlStack.push(returnHandle);

					operationStack.pop();
				}
				else
				{
					unitMagic* uM = operationStack.top().magicPtr;
					int pC = 0;//pC: 当前已经传入了的参数的计数（paramCount）；数量符合要求时停止传入参数。
					int tC = operationStack.top().magicPtr->paramCount;
					uM->paramList.resize(tC);

					//NO ERRORS THERE, cuz errors can be found during compling.
					//参数不应出错。在编辑咒文（IDE中）时就会完全避免掉参数类型的错误。
					while (pC < tC)
					{
						uM->paramList[tC - pC - 1] = paramStack.top();
						paramStack.pop();
						pC++;
					}

					spellVariable* returnValue = uM->doMagic();

					if (returnValue)
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

				spellVariable* tmpA = paramStack.top();
				paramStack.pop();

				spellVariable* tmpB = paramStack.top();
				paramStack.pop();

				spellVariable* tmpC = new spellVariable();

				if (tmpA->type == 'n' && tmpB->type == 'n' && tmpA->number.size() == tmpB->number.size())
				{
					tmpC->type = 'n';
					tmpC->temp = true;
					int j, tl = tmpA->number.size();
					for (j = 0; j < tl; j++)
					{
						tmpC->number.push_back(tmpB->number.at(j) + tmpA->number.at(j));
					}
					operationStack.pop();

					if (tmpA->temp) delete tmpA;
					if (tmpB->temp) delete tmpB;
					paramStack.push(tmpC);
				}
				else
				{
					paramStack.push(tmpB);
					paramStack.push(tmpA);
					delete tmpC;
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

				spellVariable* tmpA = paramStack.top();
				paramStack.pop();

				spellVariable* tmpB = paramStack.top();
				paramStack.pop();

				spellVariable* tmpC = new spellVariable();

				if (tmpA->type == 'n' && tmpB->type == 'n' && tmpA->number.size() == tmpB->number.size())
				{
					tmpC->type = 'n';
					tmpC->temp = true;
					int j, tl = tmpA->number.size();
					for (j = 0; j < tl; j++)
					{
						tmpC->number.push_back(tmpB->number.at(j) - tmpA->number.at(j));
					}
					operationStack.pop();

					if (tmpA->temp) delete tmpA;
					if (tmpB->temp) delete tmpB;
					paramStack.push(tmpC);
				}
				else
				{
					paramStack.push(tmpB);
					paramStack.push(tmpA);
					delete tmpC;
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

				spellVariable* tmpA = paramStack.top();
				paramStack.pop();

				spellVariable* tmpB = paramStack.top();
				paramStack.pop();

				spellVariable* tmpC = new spellVariable();

				if (tmpA->type == 'n' && tmpB->type == 'n' && tmpA->number.size() == tmpB->number.size())
				{
					tmpC->type = 'n';
					tmpC->temp = true;
					int j, tl = tmpA->number.size();
					for (j = 0; j < tl; j++)
					{
						tmpC->number.push_back(tmpB->number.at(j) * tmpA->number.at(j));
					}
					operationStack.pop();

					if (tmpA->temp) delete tmpA;
					if (tmpB->temp) delete tmpB;
					paramStack.push(tmpC);
				}
				else
				{
					paramStack.push(tmpB);
					paramStack.push(tmpA);
					delete tmpC;
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

				spellVariable* tmpA = paramStack.top();
				paramStack.pop();

				spellVariable* tmpB = paramStack.top();
				paramStack.pop();

				spellVariable* tmpC = new spellVariable();

				if (tmpA->type == 'n' && tmpB->type == 'n' && tmpA->number.size() == tmpB->number.size())
				{
					tmpC->type = 'n';
					tmpC->temp = true;
					int j, tl = tmpA->number.size();
					for (j = 0; j < tl; j++)
					{
						tmpC->number.push_back(tmpB->number.at(j) / tmpA->number.at(j));
					}
					operationStack.pop();

					if (tmpA->temp) delete tmpA;
					if (tmpB->temp) delete tmpB;
					paramStack.push(tmpC);
				}
				else
				{
					paramStack.push(tmpB);
					paramStack.push(tmpA);
					delete tmpC;
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

				spellVariable* tmpA = paramStack.top();
				paramStack.pop();

				spellVariable* tmpB = paramStack.top();
				paramStack.pop();

				spellVariable* tmpC = new spellVariable();

				if (tmpA->type == 'n' && tmpB->type == 'n' && tmpA->number.size() == tmpB->number.size())
				{
					tmpC->type = 'n';
					tmpC->temp = true;
					int j, tl = tmpA->number.size();
					for (j = 0; j < tl; j++)
					{
						tmpC->number.push_back((double)((int)tmpB->number.at(j) % (int)tmpA->number.at(j)));
					}
					operationStack.pop();

					if (tmpA->temp) delete tmpA;
					if (tmpB->temp) delete tmpB;
					paramStack.push(tmpC);
				}
				else
				{
					paramStack.push(tmpB);
					paramStack.push(tmpA);
					delete tmpC;
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

				if (tmp == paramStack.top()) break;

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
				int numCount = (int)operationStack.top().magicPtr;
				if (paramStack.size() < numCount)
				{
					ovrFlag = true;
					break;
				}

				spellVariable* ans = new spellVariable();
				ans->temp = true;
				
				stack<spellVariable*> tmpStack;
				char typ = paramStack.top()->type;
				int pC = 0;

				while (pC < numCount)
				{
					if (paramStack.top()->type == typ)
					{
						tmpStack.push(paramStack.top());
						paramStack.pop();
					}
					else
					{
						//throw error
						delete ans;
						ovrFlag = true;
						break;
					}
					pC++;
				}

				ans->type = typ;

				paramStack.push(ans);

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
			break;

			case '(':
				if (op.type == ')')
				{
					operationStack.pop();
					return false;
				}
				else
				{
					ovrFlag = true;
					break;
				}
			break;
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

int spellAnalyser::readConst(string spellStr, int startPos, spellVariable *& outputValue)
{
	int i = 0, len = spellStr.length();
	string ansStr = "";
	spellVariable* ansVar = new spellVariable();

	for (i = startPos; i < len; i++)
	{
		if ((spellStr[i] >= 'a' && spellStr[i] <= 'z') || (spellStr[i] >= 'A' && spellStr[i] <= 'Z') || (spellStr[i] == '_') || (spellStr[i] >= '0' && spellStr[i] <= '9'))
		{
			ansStr = ansStr + spellStr[i];
		}
		else
		{
			break;
		}
	}

	//================Consts here================

	if (ansStr == "FP")		//Face Pos
	{
		ansVar->type = 'n';
		ansVar->temp = true;

		//For testing, face pos always equals to vec3(0,0,0)
		ansVar->number.push_back(0);
		ansVar->number.push_back(0);
		ansVar->number.push_back(0);
	}

	//================Consts  end================

	outputValue = ansVar;
	return i - 1;
}

/*
魔晶石的触发和供能可能相互独立。供能需要向其施加各属性的属性力（但不能超出上限，同时每种魔晶石各自的承受能力是不同的，比如火魔晶石可能需要滴水不沾），触发需要一个上升沿的纯粹脉冲（待定）
*/