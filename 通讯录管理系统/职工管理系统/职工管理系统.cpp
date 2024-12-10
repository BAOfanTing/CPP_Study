#include <iostream>
using namespace std;
#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

//void test() 
//{
//	Worker* worker = NULL;
//	worker = new Eployee(1,"张三",1);
//	worker->ShowInfo();
//	delete worker;
//
//	worker = new Manager(2, "李四", 2);
//	worker->ShowInfo();
//	delete worker;
//
//	worker = new Boss(3, "王五", 3);
//	worker->ShowInfo();
//	delete worker;
//}


int main()
{
	WorkerManager mm;
	

	int choice = 0;
	while (true)
	{
		mm.showMenu();
		cout<<"请输入选择"<<endl;
		cin>>choice;

		switch (choice)
		{
		case 0: //退出系统
			mm.exitManager();
			break;
		case 1: //添加职工
			mm.Add_Emp();
			break;
		case 2: //显示职工
			mm.Show_Emp();
			break;
		case 3: //删除职工
			mm.Del_Emp();
			break;
		case 4: //修改职工
			mm.Mod_Emp();
			break;
		case 5: //查找职工
			mm.Find_Emp();
			break;
		case 6: //排序职工
			mm.Sort_Emp();
			break;
		case 7: //清空文件
		mm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}


	system("pause");
	return 0;
}