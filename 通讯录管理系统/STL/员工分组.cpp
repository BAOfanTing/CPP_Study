#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <algorithm>

class Worker
{
public:

	string m_Name;
	int m_Salary;
};

void createWorker(vector<Worker>& v)
{
	string name = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++)
	{
		Worker worker;
		/*worker.m_Name = "职工"+name[i];*/

		worker.m_Name = "职工";
		worker.m_Name += name[i];
		worker.m_Salary = rand() % 10001 + 10000;

		v.push_back(worker);
	}


}

void setGroup(vector<Worker>& v, multimap<int, Worker>& m)
{
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++)
	{
		int ID = rand() % 3;
		m.insert(make_pair(ID, *it));
	}
}
void showWorker(multimap<int, Worker>& m, int key)
{
	switch(key)
	{
	case 0:
	{
		cout << "策划部门有：" << endl;
		break;
	}
	case 1:
	{
		cout << "美术门有：" << endl;
		break;
	}
	case 2:
	{
		cout << "程序有：" << endl;
		break;
	}
	}
	multimap<int, Worker>::iterator pos = m.find(key);
	int num = m.count(key);
	int index = 0;
	for (; pos != m.end() && index < num; pos++, index++)
	{
		cout << "name: " << (pos->second).m_Name << "salary: " << (pos->second).m_Salary << endl;
	}

}
int main()
{
	vector<Worker> vWorker;
	createWorker(vWorker);


	multimap<int, Worker> mWorker;
	setGroup(vWorker, mWorker);
	/*for (vector<Worker>::iterator it = vWorker.begin();it != vWorker.end();it++)
	{
		cout<<it->m_Name<<" "<< it->m_Salary<<endl;
	}*/
	showWorker(mWorker, 0);
	showWorker(mWorker, 1);
	showWorker(mWorker, 2);

	system("pause");
	return 0;
}