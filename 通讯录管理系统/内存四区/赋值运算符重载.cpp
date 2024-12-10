#include <iostream>
#include <fstream>
#include <string>
#include "MyArr.hpp"
using namespace std;


class Person
{
public:
	Person() {};
	Person(string name, int age)
	{
		this->m_Age = age;
		this->m_Name = name;
	}
	string m_Name;
	int m_Age;
};

void printIntArray(MyArry<int>& arr) {
	for (int i = 0; i < arr.getSize(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
void printIntArray2(MyArry<Person>& arr) {
	for (int i = 0; i < arr.getSize(); i++) {
		cout << arr[i].m_Name << " "<< arr[i].m_Age<<" ";
	}
	cout << endl;
}
//void test01()
//{
//	MyArry<int> arr(5);
//	
//	for (int i = 0;i<arr.m_Capacity;i++)
//	{
//		arr.Push_Back(i);
//	}
//	cout << "array1打印输出：" << endl;
//	printIntArray(arr);
//	cout << "array1的大小：" << arr.getSize() << endl;
//	cout << "array1的容量：" << arr.getCapacity() << endl;
//
//	cout << "--------------------------" << endl;
//
//	MyArry<int> arr2(arr);
//
//	cout<<"arr2-----------"<<endl;
//	printIntArray(arr2);
//	arr2.Pop_Back(1);
//	cout << "array2的大小：" << arr2.getSize() << endl;
//	cout << "array的容量：" << arr2.getCapacity() << endl;
//}
void test02()
{
	MyArry<Person> arr2(10);

	Person p1("abc",12);
	Person p2("a", 125);
	Person p3("老三", 126);
	Person p4("老四", 124);
	Person p5("老五", 133);

	arr2.Push_Back(p1);
	arr2.Push_Back(p2);
	arr2.Push_Back(p3);
	arr2.Push_Back(p4);
	arr2.Push_Back(p5);
	printIntArray2(arr2);

}


int main() {

	//test01();

	test02();

	system("pause");

	return 0;
}