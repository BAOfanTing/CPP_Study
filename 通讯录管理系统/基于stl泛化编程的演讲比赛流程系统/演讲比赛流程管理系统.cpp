#include<iostream>
#include <string>
using namespace std;
#include "speechManager.h"
#include <ctime>
int main() {

	SpeechManager sm;
	
	//随机数种子
	srand((unsigned int)time(NULL));
	int choice = 0;

	while (true)
	{	
		
		/*system("cls");*/
		sm.showMenu();
		cout << "请输入您的选择： " << endl;
		cin >> choice; // 接受用户的选项
		
		switch (choice)
		{
		case 1:  //开始比赛
			sm.startSpeech();
			break;
		case 2:  //查看记录
			sm.showRecord();
			break;
		case 3:  //清空记录
			sm.cleanRecord();
			break;
		case 0:  //退出系统
			sm.exitSystem();
			break;
		default:
			system("cls"); //清屏
			break;
		}
	}
	system("pause");

	return 0;
}