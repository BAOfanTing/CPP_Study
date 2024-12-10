#pragma once
#include <iostream>
#include <string>
using namespace std;

template<class T>
class MyArry
{

public:
	T* pAddress;

	int m_Capacity;

	int m_Size;

public:
	MyArry(int Capacity)
	{
		cout<<"construct"<<endl;
		this->m_Capacity = Capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];

	}
	MyArry(const MyArry& arr)
	{
		cout << "copy construct" << endl;
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		//如果T为对象，而且还包含指针，必须需要重载 = 操作符，因为这个等号不是 构造 而是赋值，
		// 普通类型可以直接= 但是指针类型需要深拷贝
		this->pAddress = new T[arr.m_Capacity];

		for (int i = 0;i<this->m_Size;i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	MyArry& operator=(MyArry& p)
	{
		if (this->pAddress != NULL )
		{
			delete this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
		this->m_Capacity = p.m_Capacity;
		this->m_Size = p.m_Size;
		this->pAddress = new T[p.m_Capacity];
		for (int i = 0;i<this->m_Size;i++)
		{
			this->pAddress[i] = p.pAddress[i];
		}
		return *this;
	}
	~MyArry()
	{
		cout << "析构" << endl;
		if (this->pAddress != NULL )
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}
	void Push_Back(const T& val)
	{
		//判断容量是否能装下
		if (this->m_Capacity == this->m_Size)
		{
			cout << "装满了" << endl;
			return;
		}
		this->pAddress[this->m_Size] = val;//在数组的末尾插入
		this->m_Size++;
	}
	void Pop_Back(const T& val)
	{
		if (this->m_Size == 0)
		{
			cout << "没有元素"<<endl;
				return;
		}
		for (int i =1;i<val;i++)
		{
			this->m_Size--;
		}
		
	}
	T& operator[](int index)
	{
		return this->pAddress[index];
	}
	int getCapacity()
	{
		return this->m_Capacity;
	}
	int getSize()
	{
		return this->m_Size;
	}
};
