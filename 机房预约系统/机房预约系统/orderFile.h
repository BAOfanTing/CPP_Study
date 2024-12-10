#pragma once
#include <iostream>
using namespace std;
#include <map>
#include <fstream>
#include "globaFile.h"

class OrderFile
{
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//记录容器，int是条数，value是记录的键值对
	map<int,map<string, string>> m_orderData;

	//记录条数
	int m_Size;
};