#include <iostream>
using namespace std;

#include <string>


class MyAdd
{
public:
	int operator()(int v1, int v2)
	{
		return v1+v2;
	}
};
//2、函数对象可以有自己的状态
class MyPrint
{
public:
	MyPrint()
	{
		count = 0;
	}
	void operator()(string test)
	{
		cout << test << endl;
		count++; //统计使用次数
	}

	int count; //内部自己的状态
};
//void test02()
//{
//	MyPrint myPrint;
//	myPrint("hello world");
//	myPrint("hello world");
//	myPrint("hello world");
//	cout << "myPrint调用次数为： " << myPrint.count << endl;
//}
//3、函数对象可以作为参数传递
void doPrint(MyPrint& mp, string test)
{
	mp(test);
}

void test03()
{
	MyPrint myPrint;
	doPrint(myPrint, "Hello C++");
}



