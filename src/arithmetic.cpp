// ���������� ������� � ������� ��� ���������� �������������� ���������

#include "..\include\arithmetic.h"

Term::Term(double _num): num(_num), typeL(1) {};

Term::Term(char _operation) 
{
	if ((_operation == '~') || (_operation == '+') || (_operation == '-') || (_operation == '*') || (_operation == '/') || (_operation == '(') || (_operation == ')'))
	{
		procedure = _operation;
		typeL = 2;
	}
	else
	{
		cout << endl;
		throw "Error: not correct symbol procedure";
	}
}

Term::Term(string _alternating)
{
	size_t tmp = true;
	for (size_t i = 0; i < _alternating.length(); i++)
	{ 
		if ((_alternating[i] < 'a') || (_alternating[i] > 'z'))
		{
			tmp = false;
			cout << endl;
			throw "Error: not correct symbol int variety-parameter";
		}
	}

	if (tmp == true)
	{
		alternative = _alternating;
		typeL = 3;
	}
}

double Term::getNumber()
{
	return num;
}

char Term::getOperation()
{
	return procedure;
}

string Term::getAlternating()
{
	return alternative;
}

size_t Term::getTypeLexeme()
{
	return typeL;
}

size_t Term::getPriorityOperation()
{
	switch (procedure)
	{
	case '(':
	{
		return 0;
	}
	case ')':
	{
		return 0;
	}
	case '+':
	{
		return 1;
	}
	case '-':
	{
		return 1;
	}
	case '*':
	{
		return 2;
	}
	case '/':
	{
		return 2;
	}
	case '~':
	{
		return 3;
	}
	}
}

void Term::printT()
{
	switch (typeL)
	{
	case 1:
	{
		cout << num << " ";
		break;
	}
	case 2:
	{
		cout << procedure << " ";
		break;
	}
	case 3:
	{
		cout << alternative << " ";
		break;
	}
	}
}

void Arithmetic::translateStrToTerm(string str)
{
	bool tmp = true;
	size_t countBrackets = 0;
	size_t size = str.size();
	size_t countSpace = 0;

	if ((str[0] == '+') || (str[0] == '*') || (str[0] == '/'))
	{
		throw "Error: binary opeartions is at first position";
	}

	if ((str[str.size() - 1] == '+') || (str[str.size() - 1] == '-') || (str[str.size() - 1] == '*') || (str[str.size() - 1] == '/'))
	{
		throw "Error: binary opeartions is at last position";
	}

	for (size_t i = 0; i < str.length();)
	{
		if (str[i] == ' ')
		{
			countSpace++;
			i++;
			continue;
		}

		if ((str[i] < '(') || (str[i] == ',') || ((str[i] > '/') && (str[i] < '0')) || ((str[i] > '9') && (str[i] < 'a')) || (str[i] > 'z'))
		{
			throw "Error: in str inccorect symbol";
		}

		if ((str[i] == '+') || (str[i] == '*') || (str[i] == '/'))
		{
			Term procedure(str[i]);
			term.push_back(procedure);
			i++;
			continue;
		}

		if (str[i] == '-')
		{
			if (i == 0)
			{
				Term un_minus('~');
				term.push_back(un_minus);
				i++;
				continue;
			}
			else
			{
				if ((term[i - countSpace - 1].getOperation() != ')') && (term[i - countSpace - 1].getTypeLexeme() == 2))
				{
					Term un_minus('~');
					term.push_back(un_minus);
					i++;
					continue;
				}
				else
				{
					Term minus('-');
					term.push_back(minus);
					i++;
					continue;
				}
			}
		}
			
		if ((str[i] >= 'a') && (str[i] <= 'z'))
		{
			string alternatings;
			while ((str[i] >= 'a') && (str[i] <= 'z'))
			{
				alternatings = alternatings + str[i];
				i++;
			}
			Term _alternatings(alternatings);
			term.push_back(alternatings);
			continue;
		}

		if ((str[i] >= '0') && (str[i] <= '9') || (str[i] == '.'))
		{
			string numbers;
			size_t tmpPoint = 0;
			while (str[i] >= '0' && str[i] <= '9' || (str[i] == '.'))
			{
				numbers = numbers + str[i];
				i++;
				if (str[i] == '.')
				{
					tmpPoint++;
				}
				if (tmpPoint > 1)
				{
					throw "Error: More then 1 point";
				}
				countSpace++;
			}

			double tmp = stof(numbers);
			Term _numbers(tmp);
			term.push_back(tmp);
			countSpace--;
			continue;
		}

		if (str[i] == '(')
		{
			countBrackets++;
			tmp = false;

			if ((i < size) && ((str[i + 1] == '+') || (str[i + 1] == '-') || (str[i + 1] == '*') || (str[i + 1] == '/')))
			{
				throw "Error: procedure is after openning bracket";
			}

			if (i != 0 && str[i - 1] >= '0' && str[i - 1] <= '9')
			{
				throw "Error: number is before open bracket without procedure";
			}

			Term _bracket(str[i]);
			term.push_back(_bracket);
			i++;
			continue;
		}
		
		if (str[i] == ')')
		{
			countBrackets--;
			tmp = true;
			Term _bracket(str[i]);
			term.push_back(_bracket);
			i++;
			continue;
		}
	}

	if (tmp == false || countBrackets != 0)
	{
		throw "Error: More or Less brackets";
	}
}

void Arithmetic::TermToPolishNote()
{
	size_t size = term.size();
	Stack <Term> procedure;

	for (size_t i = 0; i < size; i++)
	{
		if (term[i].getTypeLexeme() == 1)
		{
			pNote.push_back(term[i]);
			continue;
		}

		if (term[i].getTypeLexeme() == 3)
		{
			pNote.push_back(term[i]);
			continue;
		}

		if (term[i].getOperation() == '(')
		{
			procedure.Push(term[i]);
			continue;
		}

		if (term[i].getOperation() == ')')
		{
			try
			{
			while (procedure.GetLastEl().getOperation() != '(')
			{
				pNote.push_back(procedure.Pop());
			}
			procedure.Pop();
			continue;
			}
			catch (char* error)
			{
				if (error == "Stack is Empty")
				{
					throw "Error: havent allowing open bracket";
				}
			}
		}

		if (term[i].getOperation() == '~')
		{
			procedure.Push(term[i]);
		}

		if ((term[i].getOperation() == '+') ||( term[i].getOperation() == '-') || (term[i].getOperation() == '*') || (term[i].getOperation() == '/'))
		{
			while ((!procedure.IsEmpty()) && (procedure.GetLastEl().getPriorityOperation()) >= (term[i].getPriorityOperation()))
			{
				pNote.push_back(procedure.Pop());
			}
			procedure.Push(term[i]);
		}
	}

	while (!procedure.IsEmpty())
	{
		pNote.push_back(procedure.Pop());
	}
}

void Arithmetic::calculate()
{
	Stack <Term> numbers;
	Term termleftV, termrightV;
	double leftV = 0;
	double rightV = 0;
	double resultOperation = 0;

	unordered_map<string, double> value;

	for (size_t i = 0; i < pNote.size(); i++)
	{
		
		if (pNote[i].getTypeLexeme() == 3)
		{
			if (value.count(pNote[i].getAlternating()) != 0)
			{
				double tmp = 0.0;
				tmp = value.at(pNote[i].getAlternating());
				numbers.Push(tmp);
				continue;
			}
			else
			{
				cout << "Term has variable " << endl << " Give value " << pNote[i].getAlternating() << ":";
				double tmp = 0.0;
				cin >> tmp;
				value.insert(unordered_map<string, int>::value_type(pNote[i].getAlternating(), tmp));
				numbers.Push(tmp);
				continue;
			}
		}
		

		if (pNote[i].getTypeLexeme() == 1)
		{
			numbers.Push(pNote[i].getNumber());
			continue;
		}

		if (pNote[i].getOperation() == '~')
		{
			resultOperation = (-1) * numbers.Pop().getNumber();
			numbers.Push(resultOperation);
			continue;
		}
		else
		{
			try
			{
			termrightV = numbers.Pop();
			termleftV = numbers.Pop();
			leftV = termleftV.getNumber();
			rightV = termrightV.getNumber();
			}
			catch (char* error)
			{
				if (error == "Stack is Empty")
				{
					throw "Error: opearand is miss";
				}
			}

			switch (pNote[i].getOperation())
			{
			case '+':
			{
				resultOperation = leftV + rightV;
				break;
			}
			case '-':
			{
				resultOperation = leftV - rightV;
				break;
			}
			case '*':
			{
				resultOperation = leftV * rightV;
				break;
			}
			case '/':
			{
				if (rightV == 0)
				{
					throw "Division by zero";
				}
				resultOperation = leftV / rightV;
				break;
			}
			}

			numbers.Push(resultOperation);
		}
	}

		try
		{ 
		Term resultT = numbers.Pop();
		result = resultT.getNumber();
		cout << result;
		}
		catch (char* error)
		{
			throw "Error: term was empty";
		}
}

void Arithmetic::PrintVectP()
{
	for (size_t i = 0; i < pNote.size(); i++)
	{
		pNote[i].printT();
	}

	cout << endl;
}

void Arithmetic::PrintVecT()
{
	for (size_t i = 0; i < term.size(); i++)
	{
		term[i].printT();
	}
	cout << endl;
}

double Arithmetic::GetResult()
{
	return result;
}
