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
	cout << "��ӭ����" << endl;
	
}

int log()
{
	for (int i = 1; i <= len; i++)
	{
		cout << "��¼" << i << "." << arr[i] << endl;
	}
}

void save()
{
	len++;
	cout << "������Ҫ���������" << endl; 
	string s;
	cin >> s;
	arr[len] = s;
	
}

void mydelete()
{
	log();
	cout << "���" << endl;
	cout << "��Ҫɾ����һ����" << endl;
	int x;
	cin >> x;
	if (arr[x].size())
	{
		cout << "ȷ��Ҫɾ��" <<arr[x] << "��" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2. �ҲŲ���" << endl;
		cin >> x;
		if ( x == 1)
		{
			// ɾ�����߼� 
		}
	}
	else
	{
		
	 } 
}

void menu()
{
	cout << "1.�洢һ��������" << endl;
	cout << "2.��ʾ����" << endl; 
	cout << "3.ɾ��һ��" << endl; 
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

