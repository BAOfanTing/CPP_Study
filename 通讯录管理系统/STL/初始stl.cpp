#include <iostream>
using namespace std;
#include <map>
#include <string>

class MyCompare
{
public:
	bool operator()(int val1, int val2) const
	{
		return val1>val2;
	}
};
void printMap(map<int, int,MyCompare>& m)
{
	for (map<int, int, MyCompare>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}
	cout << endl;

}

void test01()
{
	map<int, int,MyCompare> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(3, 20));
	m.insert(pair<int, int>(2, 30));

	printMap(m);
}

