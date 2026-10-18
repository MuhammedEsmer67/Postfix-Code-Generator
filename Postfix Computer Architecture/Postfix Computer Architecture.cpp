#include <iostream>
#include <stack>
#include <string>

using namespace std;

class clsCodeGenerator
{
private:
	
	stack<string> _Operands;
	string _Postfix;

	bool isReady(int Index) { return (_Operands.size() > 1 && (_Postfix[Index] == '+' || _Postfix[Index] == '-' || _Postfix[Index] == '*' || _Postfix[Index] == '/')); }

public:

	clsCodeGenerator(string Postfix) { _Postfix = Postfix; }

	void PostfixOperation() 
	{
		int TempCounter = 0;

		for (int i = 1; i <= _Postfix.length(); i++)
		{
			if (_Postfix[i - 1] >= 65 && _Postfix[i - 1] <= 90)
				_Operands.push(string(1, _Postfix[i - 1]));
			else
			{
				if (isReady(i - 1))
				{
					string Top = _Operands.top();
					_Operands.pop();

					cout << "LD " << _Operands.top() << endl;

					switch (_Postfix[i - 1])
					{
						case '+':
							cout << "AD " << Top << endl;
							break;
						case '-':
							cout << "SB " << Top << endl;
							break;
						case '*':
							cout << "ML " << Top << endl;
							break;
						case '/':
							cout << "DV " << Top << endl;
							break;
						default:
							cout << "Invalid Operation Type!\n";
							break;
					}

					string Temp = "Temp" + to_string(++TempCounter);
					cout << "ST " << Temp << endl;

					_Operands.pop();
					_Operands.push(Temp);
				}
				else
					cout << "Invalid Postfix Operation!\n";
			}
		}
	}

};

int main()
{
	string Postfix = "";
	cout << "Please enter the postfix expression: ";
	cin >> Postfix;
	cout << endl;

	clsCodeGenerator Generator1(Postfix);

	Generator1.PostfixOperation();
	
	return 0;
}
