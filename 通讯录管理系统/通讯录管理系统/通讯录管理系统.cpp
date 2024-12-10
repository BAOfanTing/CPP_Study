#include<iostream>
#include <string>
#define Max 1000
using namespace std;

struct Person 
{
	string m_Name; //姓名
	int m_Sex; //性别：1男 2女
	int m_Age; //年龄
	string m_Phone; //电话
	string m_Addr; //住址
};



struct Addressbooks 
{
	struct Person personArray[Max];
	int m_Size;
};


void Addperson(Addressbooks* abs)
{
	if (abs->m_Size == 1000)
	{
		cout<<"人已经满了"<<endl;
		return ;
	}
	else
	{
		string Name;
		cout<<"请输入姓名"<<endl;
		cin>>Name;
		abs->personArray[abs->m_Size].m_Name = Name;

		cout << "请输入性别：" << endl;
		cout << "1 -- 男" << endl;
		cout << "2 -- 女" << endl;

		int sex = 0;
		while (true)
		{
			cin>>sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			else
			{
				cout<<"重新输入"<<endl;
			}
		}

		//年龄
		cout << "请输入年龄：" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//联系电话
		cout << "请输入联系电话：" << endl;
		string phone;
		cin>>phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//家庭住址
		cout << "请输入家庭住址：" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//更新通讯录人数
		abs->m_Size++;

		cout << "添加成功" << endl;
		system("pause");
		system("cls");
	}
}


void ShowPerson(Addressbooks* abs)
{
	if (abs->m_Size==0)
	{
		cout<<"no body"<<endl;
	}
	else
	{
		for (int i = 0;i<abs->m_Size;i++)
		{
			cout << "姓名：" << abs->personArray[i].m_Name << "\t";
			cout << "性别：" << (abs->personArray[i].m_Sex ==1 ? "男":"女") << "\t";
			cout << "年龄：" << abs->personArray[i].m_Age << "\t";
			cout << "电话：" << abs->personArray[i].m_Phone << "\t";
			cout << "住址：" << abs->personArray[i].m_Addr << endl;
		}
	}
	system("pause");
	system("cls");
}

int CheckPerson(Addressbooks* abs,string Name)
{
	
	for (int i=0;i<abs->m_Size;i++)
	{
		if (abs->personArray[i].m_Name == Name)
		{
			return i;
		}
	}

	return -1;
}

void  DeletePerson(Addressbooks* abs)
{
	string Name;
	cout << "请输入删除的姓名" << endl;
	cin >> Name;
	int index = CheckPerson(abs, Name);
	if (index != -1)
	{
		for (int i = index;i<abs->m_Size;i++)
		{
			abs->personArray[i] = abs->personArray[i+1];
		}
		abs->m_Size--;
		cout << "删除成功" << endl;
	}
	else
	{
		cout<<"查无此人"<<endl;
	}
	system("pause");
	system("cls");

}
void CheckAndShowPerson(Addressbooks* abs)
{
	cout << "请输入您要查找的联系人" << endl;
	string name;
	cin >> name;
	int Index = CheckPerson(abs,name);
	if (Index != -1)
	{
		cout << "姓名：" << abs->personArray[Index].m_Name << "\t";
		cout << "性别：" << abs->personArray[Index].m_Sex << "\t";
		cout << "年龄：" << abs->personArray[Index].m_Age << "\t";
		cout << "电话：" << abs->personArray[Index].m_Phone << "\t";
		cout << "住址：" << abs->personArray[Index].m_Addr << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}

	system("pause");
	system("cls");

}
void ChangePerson(Addressbooks* abs)
{
	cout << "请输入您要查找的联系人" << endl;
	string name;
	cin >> name;
	int Index = CheckPerson(abs, name);
	if (Index != -1)
	{
		while (true)
		{
			int select = 0;
			cout << "*****  1、修改名字  *****" << endl;
			cout << "*****  2、修改性别 *****" << endl;
			cout << "*****  3、修改年龄  *****" << endl;
			cout << "*****  4、修改电话  *****" << endl;
			cout << "*****  5、修改地址  *****" << endl;
			cout << "*****  0、修改完毕  *****" << endl;
			cin >> select;
			string change_name;
			int sex;
			int age;
			string phone;
			string addr;
			switch (select)
			{
			case 1:
				cout << "请输入名字" << endl;
				cin >> change_name;
				abs->personArray[Index].m_Name = change_name;
				break;
			case 2:
				cout << "请输入性别" << endl;
				cin >> sex;
				abs->personArray[Index].m_Sex = sex;
				break;
			case 3:
				cout << "请输入年龄" << endl;
				cin >> age;
				abs->personArray[Index].m_Age = age;
				break;
			case 4:
				cout << "请输入电话" << endl;
				cin >> phone;
				abs->personArray[Index].m_Phone = phone;
				break;
			case 5:
				cout << "请输入地址" << endl;
				cin >> addr;
				abs->personArray[Index].m_Addr = addr;
				break;
			case 0:
				cout << "修改完成" << endl;
				system("pause");
				system("cls");
				return;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		cout << "查无此人" << endl;
	}

	system("pause");
	system("cls");


}
void CleanPerson(Addressbooks* abs)
{
	abs->m_Size = 0;
	cout << "通讯录已清空" << endl;
	system("pause");
	system("cls");
}
void ShowMenu()
{
	cout << "***************************" << endl;
	cout << "*****  1、添加联系人  *****" << endl;
	cout << "*****  2、显示联系人  *****" << endl;
	cout << "*****  3、删除联系人  *****" << endl;
	cout << "*****  4、查找联系人  *****" << endl;
	cout << "*****  5、修改联系人  *****" << endl;
	cout << "*****  6、清空联系人  *****" << endl;
	cout << "*****  0、退出通讯录  *****" << endl;
	cout << "***************************" << endl;
}

int main()
{	
	//创建通讯录
	Addressbooks abs;
	//初始化通讯录中人数
	abs.m_Size = 0;

	int select = 0;
	
	while (true)
	{
		ShowMenu();
		cin>>select;

		switch (select)
		{
		case 1:  //添加联系人
			Addperson(&abs);
			break;
		case 2:  //显示联系人
			ShowPerson(&abs);
			break;
		case 3:  //删除联系人
			DeletePerson(&abs);
			break;
		case 4:  //查找联系人
			CheckAndShowPerson(&abs);
			break;
		case 5:  //修改联系人
			ChangePerson(&abs);
			break;
		case 6:  //清空联系人
			break;
		case 0:  //退出通讯录
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}


	}
	system("pause");
	return 0;

}