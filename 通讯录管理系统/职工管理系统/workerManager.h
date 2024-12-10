#pragma once
#include<iostream>
using namespace std;
#include "worker.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include <fstream>
#define  FILENAME "empFile.txt"


class WorkerManager
{
public:
	
	WorkerManager();

	~WorkerManager();

	void showMenu();
	void exitManager();
	//记录文件中的人数个数
	int m_EmpNum;
	//员工数组的指针,指向指针的指针
	Worker ** m_EmpArray;

	//增加职工
	void Add_Emp();
	//保存文件
	void save();
	bool m_FileIsEmpty;

	//统计人数
	int get_EmpNum();
	//初始化员工
	void init_Emp();
	//显示职工
	void Show_Emp();
	//删除职工
	void Del_Emp();
	//按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
	int IsExist(int id);
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	//排序
	void Sort_Emp();
	//删除
	void Clean_File();
};