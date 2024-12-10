#include "boss.h"

Boss::Boss(int id, string name, int did)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

void Boss::ShowInfo()
{
	cout << "职工编号： " << this->m_ID
		<< " \t职工姓名： " << this->m_Name
		<< " \t岗位：" << this->GetDeptName()
		<< " \t岗位职责：管理公司所有事务" << endl;
}

string Boss::GetDeptName()
{
	return string("总裁");
}
