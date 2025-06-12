#include<iostream>
using namespace std;


struct Node
{
	string name;	
};

string arr[1000];
int len = 0;

void welcome() 
{
	cout << "欢迎光临" << endl;
	
}

int log()
{
	for (int i = 1; i <= len; i++)
	{
		cout << "记录" << i << "." << arr[i] << endl;
	}
}

void save()
{
	len++;
	cout << "输入你要保存的内容" << endl; 
	string s;
	cin >> s;
	arr[len] = s;
	
}

void mydelete()
{
	log();
	cout << "你好" << endl;
	cout << "你要删除哪一条？" << endl;
	int x;
	cin >> x;
	if (arr[x].size())
	{
		cout << "确认要删除" <<arr[x] << "吗？" << endl;
		cout << "1.确认" << endl;
		cout << "2. 我才不呢" << endl;
		cin >> x;
		if ( x == 1)
		{
			// 删除的逻辑 
		}
	}
	else
	{
		
	 } 
}

void menu()
{
	cout << "1.存储一条新数据" << endl;
	cout << "2.显示所有" << endl; 
	cout << "3.删除一条" << endl; 
	string x;
	cin >> x;
	if (x == "1")
	{
		save();
	}
	if (x == "2")
	{
		log();
	}
	if (x == "3")
	{
		mydelete();
	}
}

int main()
{
	welcome();
	while (true)
	{
	
		menu();
		for (int i = 1; i <= 3; i++)
		{
			cout << endl;
		}	
	}

		
}

