#include "teacher.h"

#include"teacher.h"

//默认构造
Teacher::Teacher()
{
}

//有参构造 (职工编号，姓名，密码)
Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Password = pwd;
}

//菜单界面
void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i<of.m_Size;i++)
	{
		cout << i + 1 << "、 ";
		cout << "预约日期： 周" << of.m_orderData[i]["date"];
		cout << " 时段：" <<(of.m_orderData[i]["interval"] == "1" ? "上午":"下午");
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房：" << of.m_orderData[i]["roomId"];
		string status = "状态：";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout<<status<<endl;	
	}
	system("pause");
	system("cls");
}

//审核预约
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	vector<int> v;
	int index = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index + 1 << "、 ";
			cout << "预约日期： 周" << of.m_orderData[i]["date"];
			cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 学号：" << of.m_orderData[i]["stuId"];
			cout << " 姓名：" << of.m_orderData[i]["stuName"];
			cout << " 机房：" << of.m_orderData[i]["roomId"];
			cout << "状态：审核中" << endl;
			index++;
		}
			
	}
	cout << "请输入审核的预约记录,0代表返回" << endl;
	index = 0;
	int select;
	while (true)
	{
		cin>> index;
		if (index >=0 && index <= of.m_Size)
		{
			if (index == 0)
			{
				break;
			}
			cout << "请输入审核结果" << endl;
			cout << "1、通过" << endl;
			cout << "2、不通过" << endl;
			cin >> select;
			if (select == 1)
			{
				of.m_orderData[v[index - 1]]["status"] = "2";
				cout << "修改成功" << endl;
				break;
			}
			else if (select == 2)
			{
				of.m_orderData[v[index - 1]]["status"] = "-1";
				cout << "修改成功" << endl;
				break;
			}
			
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
		}
	}
	of.updateOrder();
	system("pause");
	system("cls");

}
