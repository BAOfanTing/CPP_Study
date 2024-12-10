#include <iostream>
#include <string>
using namespace std;
#include "Identity.h"
#include <fstream>
#include "globaFile.h"
#include "manager.h"
#include "student.h"
#include "teacher.h"



void managerMenu(Identity* &manager)
{
	 while (true)
	 {
		//调用管理员子菜单
		manager->operMenu();

		//将父类指针转化为子类指针，调用子类里其他接口
		Manager* man = (Manager*)manager;

		int select = 0;
		cin>>select;

		if (select == 1)  //添加账号
		{
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) //查看账号
		{
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3) //查看机房
		{
			cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4) //清空预约
		{
			cout << "清空预约" << endl;
			man->cleanFile();
		}
		else
		{
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	 }
}

void studentMenu(Identity*& student)
{
	while (true)
	{
		//学生菜单
		student->operMenu();

		//将父类指针转化为子类指针，调用子类里其他接口
		Student* stu = (Student*)student;

		int select = 0;

		cin >> select;

		if (select == 1) //申请预约
		{
			stu->applyOrder();
		}
		else if (select == 2) //查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select == 3) //查看所有预约
		{
			stu->showAllOrder();
		}
		else if (select == 4) //取消预约
		{
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->operMenu();

		//修改为子类指针
		Teacher* teac = (Teacher*)teacher;

		int select = 0;
		cin>>select;
		if (select == 1)
		{
			teac->showAllOrder();
		}
		else if (select == 2)
		{
			teac->validOrder();
		}
		else
		{
			delete teacher;
			cout<<"注销成功"<<endl;
			system("pause");
			system("cls");
			return;
		}

	}
	


}

void LoginIn(string FileName, int type)
{
	//父类指针，用于指向子类对象
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(FileName,ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
		
	}
	int id = 0;
	string name;
	string password;

	if (type == 1)//学生登录
	{
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if (type == 2) //教师登录
	{
		cout << "请输入你的职工号" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码： " << endl;
	cin >> password;

	if (type == 1)
	{
		//学生登录验证
		int fID;
		string fName;
		string fPwd;

		while (ifs >> fID && ifs>>fName && ifs>>fPwd)
		{
			if (fID == id && fName == name && fPwd == password)
			{
				cout<<"学生认证成功"<<endl;
				system("pause");
				system("cls");
				person = new Student(id,name,password);

				//进入菜单子界面
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师登录验证
		int fID;
		string fName;
		string fPwd;

		while (ifs >> fID && ifs >> fName && ifs >> fPwd)
		{
			if (fID == id && fName == name && fPwd == password)
			{
				cout << "老师认证成功" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, password);
				//进入子菜单
				teacherMenu(person);
				return ;
			}
		}
	}
	else if (type == 3)
	{
		//管理员登录验证
		string fName;
		string fPwd;

		while ( ifs >> fName && ifs >> fPwd)
		{
			if ( fName == name && fPwd == password)
			{
				cout << "管理员认证成功" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, password);

				//进入菜单子界面
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证登录失败!" << endl;

	system("pause");
	system("cls");
	return;
}


int main() {

	int select = 0;
	
	while (true)
	{
		cout << "======================  欢迎来到传智播客机房预约系统  ====================="
			<< endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";
		cin >> select;

		switch (select)
		{
		case 1://student
			LoginIn(STUDENT_FILE,1);
			break;
		case 2://teacher
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://manager
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://exit
			cout << "欢迎下一次使用" << endl;
			system("pause");
			exit(0);
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	

	system("pause");

	return 0;
}