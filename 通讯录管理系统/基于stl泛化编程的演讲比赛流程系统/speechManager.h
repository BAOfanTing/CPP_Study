#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include <map>
#include <algorithm>
#include <deque>
#include <functional>
#include "Speecher.h"
#include <numeric>
#include <fstream>

class SpeechManager
{
public:
	SpeechManager();

	~SpeechManager();

	//菜单展示
	void showMenu();
	//退出
	void exitSystem();

	//比赛选手 容器  12人
	vector<int> v1;

	//第一轮晋级容器  6人
	vector<int> v2;

	//胜利前三名容器  3人
	vector<int> vVictory;

	//存放编号 以及对应的 具体选手 容器
	map<int,Speecher> m_Speecher;

	//初始化属性
	void initSpeech();

	//初始化创建12名选手
	void createSpeaker();



	//比赛轮数
	int m_Index;


	//开始比赛
	void startSpeech();
	//抽签
	void SpeechDraw();
	//比赛
	void SpeechContest();
	//显示比赛分数
	void ShowScore();
	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	bool fileEmpty;

	map<int,vector<string>> m_Record;

	void showRecord();
	void cleanRecord();
};