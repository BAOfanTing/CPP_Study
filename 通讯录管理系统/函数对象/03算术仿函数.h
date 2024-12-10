#pragma once
#include <iostream>
#include <functional>

using namespace std;


void test01()
{
	negate<int> n;
	cout<< n(50) <<endl;

	plus<int> p;
	cout<<p(10,20)<<endl;

	multiplies<int> m;
	int a1 = 10;
	cout<<m(10,10)<<endl;
}