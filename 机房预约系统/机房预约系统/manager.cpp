#include "manager.h"
void printStudent(Student& s)
{
	cout << "学号： " << s.m_Id << " 姓名： " << s.m_Name << " 密码：" << s.m_Password << endl;
}

void printTeacher(Teacher& t)
{
	cout << "职工号： " << t.m_EmpId << " 姓名： " << t.m_Name << " 密码：" << t.m_Password << endl;
}
void printCom(ComputeRoom& c)
{
	cout << "机房号 " << c.m_ComId << " 最大数量： " << c.m_MaxNum << endl;
}

class MYfindstu
{
public:

	int id;
	MYfindstu(int _id){id = _id;}
	bool operator()(Student& s) const
	{
		return s.m_Id == id;
	}
};
class MYfindtea
{
public:

	int id;
	MYfindtea(int _id) { id = _id; }
	bool operator()(Teacher& t) const
	{
		return t.m_EmpId == id;
	}
};
//默认构造
Manager::Manager()
{
}

//有参构造
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Password =pwd; 

	//初始化容器
	initVector();

	//获取机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE,ios::in);

	ComputeRoom c;

	while (ifs >>c.m_ComId && ifs >>c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "当前机房数量为： " << vCom.size() << endl;

	ifs.close();

}

//选择菜单
void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//添加账号  
void Manager::addPerson()
{

	string filename;
	string tip;
	string Errotip;
	ofstream ofs;//文件操作对象

	int select = 0;
	while (select != 1 && select != 2)
	{
		cout << "请输入添加账号的类型" << endl;
		cout << "1、添加学生" << endl;
		cout << "2、添加老师" << endl;
		
		cin >> select;
		switch (select)
		{
			case 1:
			{
				filename = STUDENT_FILE;
				tip = "请输入学号： ";
				Errotip = "学号重复，请重新输入";
				break;
			}
			case 2:
			{
				filename = TEACHER_FILE;
				tip = "请输入职工编号：";
				Errotip = "职工号重复，请重新输入";
				break;
			}
			default:
			{
				cout<< "输入有误请重新输入"<<endl;
				break;
			}
		}
	}
	//以追加的方式写入文件
	ofs.open(filename,ios::out | ios::app);

	int id;
	string name;
	string pwd;

	cout<<tip<<endl;

	while (true)
	{
		cin>>id;
		bool is_repeat = this->checkRepeat(id, select);
		if (is_repeat)
		{
			cout<<Errotip<<endl;
		}
		else
		{
			break;
		}
	}
	

	cout << "请输入姓名： " << endl;
	cin >> name;

	cout << "请输入密码： " << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	system("pause");
	system("cls");

	ofs.close();
	//重新获取文件中的数据
	this->initVector();
}

//查看账号
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select;
	cin>>select;
	if (select ==1)
	{
		cout << "所有学生信息如下： " << endl;
		for_each(vStu.begin(),vStu.end(),printStudent);
	}
	else
	{
		cout << "所有老师信息如下： " << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	cout<<"机房信息如下："<<endl;
	for_each(vCom.begin(),vCom.end(), printCom);
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE,ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

void Manager::initVector()
{	
	//读取学生文件
	ifstream ifs;
	ifs.open(STUDENT_FILE,ios::in);
	if (!ifs.is_open())
	{
		cout<<"学生文件不存在"<<endl;
		return;
	}
	vStu.clear();
	vTea.clear();
	
	Student s;
	while (ifs>>s.m_Id && ifs>> s.m_Name && ifs>>s.m_Password)
	{
		vStu.push_back(s);
	}
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "老师文件不存在" << endl;
		return;
	}

	Teacher t;

	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Password)
	{
		vTea.push_back(t);
	}
	ifs.close();
	
	

}

bool Manager::checkRepeat(int id, int type)
{
	//学生
	if (type == 1)
	{
		vector<Student>::iterator pos = find_if(vStu.begin(),vStu.end(), MYfindstu(id));
		if (pos != vStu.end())
		{
			return true;
		}
	}
	else
	{
		vector<Teacher>::iterator pos = find_if(vTea.begin(), vTea.end(), MYfindtea(id));
		if (pos != vTea.end())
		{
			return true;
		}
	}
	
	return false;
}


