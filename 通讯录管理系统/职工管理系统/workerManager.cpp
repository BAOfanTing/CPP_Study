#include "workerManager.h"

WorkerManager::WorkerManager()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl; //测试输出
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2、文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3、文件存在且有数据
	int num = this->get_EmpNum();
	/*cout<<"职工个数为"<<num<<endl;*/
	this->m_EmpNum = num;

	//根据职工数创建数组
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//初始化职工
	this->init_Emp();

	////测试代码
	//for (int i = 0;i<this->m_EmpNum;i++)
	//{
	//	cout << "职工号： " << this->m_EmpArray[i]->m_ID
	//		<< " 职工姓名： " << this->m_EmpArray[i]->m_Name
	//		<< " 部门编号： " << this->m_EmpArray[i]->m_DeptID << endl;
	//}

}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete this->m_EmpArray;
	}
}

void WorkerManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitManager()
{
	cout << "退出欢迎使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "请输入增加职工的数量" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{	//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
			cin >> id;


			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;


			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;

			switch (dSelect)
			{
			case 1: //普通员工
				worker = new Employee(id, name, 1);
				break;
			case 2: //经理
				worker = new Manager(id, name, 2);
				break;
			case 3:  //老板
				worker = new Boss(id, name, 3);
				break;
			default:
				break;

			}

			newSpace[this->m_EmpNum + i] = worker;
			//释放原有空间
			delete[] this->m_EmpArray;
			this->m_EmpArray = newSpace;
			this->m_EmpNum = newSize;
			this->m_FileIsEmpty = false;
			//提示信息
			cout << "成功添加" << addNum << "名新职工！" << endl;
			this->save();

		}

	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	int id;
	string name;
	int dId;
	int num = 0;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//>> 默认会按照空格、换行符等空白字符进行分割
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	ifs.close();
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		switch (dId)
		{
		case 1:
			worker = new Employee(id, name, dId);
			break;
		case 2:
			worker = new Manager(id, name, dId);
			break;
		case 3:
			worker = new Boss(id, name, dId);
			break;
		default:
			break;
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
}

void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者列表为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->ShowInfo();
		}
		system("pause");
		system("cls");
	}
}

void WorkerManager::Del_Emp()
{
	int id;
	cout << "请输入需要删除的职工id" << endl;
	cin >> id;
	int index = this->IsExist(id);
	if (index == -1)
	{
		cout << "查无此人" << endl;
	}
	else
	{
		for (int i = index; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;
		this->save();
		cout << "删除成功" << endl;
	}
}

int WorkerManager::IsExist(int id)
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或者列表为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (id == this->m_EmpArray[i]->m_ID)
			{
				return i;
			}
		}
		return -1;
	}

}

void WorkerManager::Mod_Emp()
{
	int id;
	cout << "请输入需要修改的职工id" << endl;
	cin >> id;
	int index = this->IsExist(id);
	if (index == -1)
	{
		cout << "查无此人" << endl;
	}
	else
	{
		delete this->m_EmpArray[index];
		int newId = 0;
		string newName = "";
		int dSelect = 0;
		cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
		cin >> newId;

		cout << "请输入新姓名： " << endl;
		cin >> newName;

		cout << "请输入岗位： " << endl;
		cout << "1、普通职工" << endl;
		cout << "2、经理" << endl;
		cout << "3、老板" << endl;
		cin >> dSelect;

		Worker* worker = NULL;
		switch (dSelect)
		{
		case 1 :
			worker = new Employee(newId,newName,dSelect);
		case 2:
			worker = new Manager(newId, newName, dSelect);
		case 3:
			worker = new Boss(newId, newName, dSelect);
		default:
			break;
		}
		this->m_EmpArray[index] = worker;
		cout<<"修改成功"<<endl;
		this->save();	
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout<<"文件不存在或记录为空"<<endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;
		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号" << endl;
			cin >> id;
			int index = this->IsExist(id);
			if (index != -1)
			{
				cout << "查找成功" << endl;
				this->m_EmpArray[index]->ShowInfo();
			}
			else
			{
				cout << "no that people" << endl;
			}
		}
		else if (select == 2)
		{
			cout << "please input people,s name" << endl;
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					flag = true;
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_ID
						<< " 号的信息如下：" << endl;
					this->m_EmpArray[i]->ShowInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0;i<this->m_EmpNum;i++)
		{
			int MinOrMax = i;
			for (int j = i+1;j<this->m_EmpNum;j++)
			{
				if (select ==1)
				{
					if (m_EmpArray[MinOrMax]->m_ID > m_EmpArray[j]->m_ID)
					{
						MinOrMax = j;
					}
				}
				else
				{
					if (m_EmpArray[MinOrMax]->m_ID < m_EmpArray[j]->m_ID)
					{
						MinOrMax = j;
					}
				}
			}
			if (i != MinOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[MinOrMax];
				m_EmpArray[MinOrMax] = temp;

			}
		}
		cout << "排序成功,排序后结果为：" << endl;
		this->save();
		this->Show_Emp();
	}

}

void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{	
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME,ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0;i<this->m_EmpNum;i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty  = true;
		}

	}
}


