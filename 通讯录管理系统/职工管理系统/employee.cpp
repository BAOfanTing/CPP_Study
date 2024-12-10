#include "employee.h"
#include <string>



Employee::Employee(int id, string name, int did)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

void Employee::ShowInfo()
{	
	cout << "职工编号： " << this->m_ID
		<< " \t职工姓名： " << this->m_Name
		<< " \t岗位：" << this->GetDeptName()
		<< " \t岗位职责：完成经理交给的任务" << endl;
	
}

string Employee::GetDeptName()
{
	return string("员工");
}
