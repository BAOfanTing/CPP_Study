#include "speechManager.h"


SpeechManager::SpeechManager()
{
	this->initSpeech();
	//创建选手
	this->createSpeaker();

	this->loadRecord();
}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout<<"欢迎使用"<<endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	//容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speecher.clear();
	//抽签
	this->m_Index = 1;
	//讲记录容器清空
	this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{	
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0;i<nameseed.size();i++)
	{
		string name = "选手";
		name += nameseed[i];

		Speecher sp;
		sp.m_Name = name;
		for (int i = 0;i<2;i++)
		{
			sp.m_Score[i] = 0;
		}
		this->v1.push_back(i+10001);
		this->m_Speecher.insert(make_pair(i+10001,sp));
	}
	

}

void SpeechManager::startSpeech()
{
	
	//第一轮比赛
	//1、抽签
	this->SpeechDraw();

	//2、比赛
	this->SpeechContest();

	//3、显示晋级结果
	this->ShowScore();
	//第二轮比赛
	this->m_Index++;
	//1、抽签
	this->SpeechDraw();
	//2、比赛
	this->SpeechContest();
	//3、显示最终结果
	this->ShowScore();
	//4、保存分数
	this->saveRecord();

	this->initSpeech();
	//创建选手
	this->createSpeaker();

	this->loadRecord();

}

void SpeechManager::SpeechDraw()
{
	cout<<"第 "<<this->m_Index<<" 轮抽签"<<endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end();it++)
		{
			cout<<*it<<" ";
		}
		cout<<endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout<<"------------------------"<<endl;
	system("pause");

}

void SpeechManager::SpeechContest()
{
	cout << "------------- 第" << this->m_Index << "轮正式比赛开始：------------- " << endl;
	//临时容器，保存key分数 value 选手编号
	multimap<double,int,greater<double>> groupScore;
	//记录人员数，6个为1组
	int num = 0;

	vector<int> v_Src;

	if (this->m_Index==1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	for (vector<int>::iterator it = v_Src.begin();it != v_Src.end();it++)
	{
		num++;

		deque<double>d;
		for (int i=0;i<10;i++)
		{
			double score = (rand()%401+600)/10.f;
			d.push_back(score);
		}

		sort(d.begin(),d.end());//排序
		d.pop_back();	//去掉最高分
		d.pop_front();//去掉最低分
		double sum = accumulate(d.begin(),d.end(),0.0f); //获取总分
		double avg = sum/(double)d.size();//获取平均分
		//cout << "编号： " << *it  << " 选手： " << this->m_Speecher[*it].m_Name << " 获取平均分为： " << avg << endl;  //打印分数
		//放入平均分
		this->m_Speecher[*it].m_Score[this->m_Index-1] = avg;
		groupScore.insert(make_pair(avg,*it));//key是得分，val是选手编号
		if (num%6 == 0)
		{
			cout<<"第"<<num / 6<<"小组比赛名次："<<endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end();it++)
			{
				cout << "编号： " << it->second << " 选手： " << this->m_Speecher[it->second].m_Name << " 获取平均分为： " << this->m_Speecher[it->second].m_Score[this->m_Index-1] << endl;  //打印分数
			}
			int count = 0;
			//取前三名
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&& count<3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}
				
			}
			groupScore.clear();
		}
	}
	cout << "------------- 第" << this->m_Index << "轮比赛完毕  ------------- " << endl;
	system("pause");
}

void SpeechManager::ShowScore()
{
	cout<<"-------------------------第"<<this->m_Index<<"轮晋级选手信息如下--------------------"<<endl;

	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end();it++)
	{
		cout << "编号： " << *it<< " 选手： " << this->m_Speecher[*it].m_Name << " 获取平均分为： " << this->m_Speecher[*it].m_Score[this->m_Index - 1] << endl;  //打印分数
	}
	cout<<endl;
	system("pause");
	system("cls");
	this->showMenu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv",ios::out| ios::app);// 用输出的方式打开文件  -- 写文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end();it++)
	{
		ofs<<*it <<","<< m_Speecher[*it].m_Score[1]<<",";
	}
	ofs<<endl;

	//关闭文件
	ofs.close();
	cout << "记录已经保存" << endl;
	this->fileEmpty = false;
	system("pause");
}

void SpeechManager::showRecord()
{
	if (this->fileEmpty)
	{
		cout<<"文件不存在或为空"<<endl;
	}
	for (int i = 0;i<m_Record.size();i++)
	{
		cout << "第" << i + 1 << "届 " <<
			"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
			"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
			"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::cleanRecord()
{
	
	cout<<"确认清空？"<<endl;
	cout<<"1、确认"<<endl;
	cout<<"2、返回"<<endl;
	int select = 0;
	cin>>select;
	if (select == 1)
	{
		//及时文件存在也重新创建它
		ofstream ofs("speech.csv",ios::trunc);
		ofs.close();

		//初始化属性
		this->initSpeech();

		this->createSpeaker();
		this->loadRecord();
		cout << "清空完毕" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		system("pause");
		system("cls");
	}

	
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv",ios::in);//输入流对象 读取文件

	if (!ifs.is_open())
	{
		this->fileEmpty = true;
		cout<<"文件不存在"<<endl;
		ifs.close();
		return;
	}
	//文件清空
	char ch;
	ifs>>ch;
	if (ifs.eof())
	{
		this->fileEmpty = true;
		cout << "文件为空" << endl;
		ifs.close();
		return;
	}

	//否则就是存在文件
	this->fileEmpty = false;
	ifs.putback(ch);//把刚刚那个还回来

	string data;
	int index = 0;//第几届
	while (ifs>>data)
	{
		/*cout<<data<<endl;*/
		vector<string> v;
		
		int start = 0;
		int pos = -1;
		while (true)
		{
			
			pos = data.find(",", start);

			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			/*cout << temp << endl;*/
			start = pos + 1;
			v.push_back(temp);
		}
		this->m_Record.insert(make_pair(index,v));
		index ++;

		
	}
	ifs.close();
	
}


