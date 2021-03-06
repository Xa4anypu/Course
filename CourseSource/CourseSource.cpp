// CourseSource.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <list> 
#include <iostream>	
#include <fstream>
#include <cstring>

using namespace std;

struct Person
{
	int Number = 0;
	string Name = "";
	int Type = 0;
	int Amount = 0;

	bool operator <(const Person & personObj) const
	{
		return Number < personObj.Number;
	}
};

#pragma region Comparators

struct NameComparator
{
	bool operator ()(const Person & p1, const Person & p2)
	{
		if (p1.Name == p2.Name)
			return p1 < p2;
		return p1.Name < p2.Name;

	}
};

struct DepositComparator
{
	bool operator ()(const Person & p1, const Person & p2)
	{
		if (p1.Type == p2.Type)
			return p1 < p2;
		return p1.Type < p2.Type;

	}
};

struct AmountComparator
{
	bool operator ()(const Person & p1, const Person & p2)
	{
		if (p1.Amount == p2.Amount)
			return p1 < p2;
		return p1.Amount < p2.Amount;

	}
};

#pragma endregion


#pragma region Prototypes

string GetTableRow(Person person);
string GetType(int type);
string GetAmount(int amount);
string* Split(string line);
Person stringToPerson(string * line);

#pragma endregion

string path = "table.txt";

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream myfile(path);
	string line;
	/*#pragma region Header
	cout << "№\t" << "FIO\t" << "TYPE\t" << "AMOUNT\t" << endl;
	#pragma endregion*/
	list <Person> Persons;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			string * str = Split(line);
			if (line.length() > 0)
			{
				Person ps = stringToPerson(str);
				Persons.push_back(ps);
				//cout << GetTableRow(ps) << endl;
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	Persons.sort(AmountComparator());

	for (auto v : Persons)
	{
		//if (v.Type == 1)
		{
			cout << GetTableRow(v) << endl;
		}
	}

    return 0;
}

string GetTableRow(Person person)
{
	string res = "";
	

	res = to_string(person.Number) + "\t" + person.Name + "\t" +  GetType(person.Type) + "\t" + GetAmount(person.Amount);

	return res;
}

string GetType(int type)
{
	string res = "Неизвестный вклад";
	switch (type)
	{
	case 1:
		res = "Срочный";
		break;
	case 2:
		res = "Депозит";
		break;
	case 3:
		res = "Пенсионный";
		break;
	}
	return res;
}

int SetType(string type)
{
	if (type == "Срочный")
		return 1;
	if (type == "Депозит")
		return 2;
	if (type == "Пенсионный")
		return 3;
}

string GetAmount(int amount)
{
	string res = to_string(amount);
	return  res;
}

string* Split(string line)
{
	int count = 4;

	string * str = new string[count];

	int n = 0;
	string word = "";
	line += "*";
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] != '\t')
		{
			word += line[i];
		}
		else
		{
			if (word.length() > 0)
			{
				str[n] = word;
				n++;
				word = "";
			}
		}
	}
	str[3] = word;
	return str;
}

Person stringToPerson(string * line)
{
	Person ps;
	ps.Number = atoi(line[0].c_str());
	ps.Name = line[1];
	ps.Type = SetType(line[2]);
	ps.Amount = atoi(line[3].c_str());
	return ps;
}