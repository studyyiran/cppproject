#include <iostream>
#include <cstdlib>
#include<ctime>
using namespace std;

struct Hero {
	int x;
	int y;
	char pic;
};

Hero player = {2, 2, '6'};


struct Node {
    int type; // 0: �ݵ�, 1: ˮ, 2: ɳĮ����
    char pic;
};

const int Width = 15;
const int Height = 15;
Node arr[Height][Width];

char get_pic(int type) {
    if(type==0) return '#'; // grass
    if(type==1) return 'X'; // water
    if(type==2) return '='; // sand
    return '?';
}

int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}

int getRandomType(int i, int j)
{
	 int t;
    if(i==0 && j==0) {
        t = randint(0,2); // ���Ͻ����
    } else {
        int neighbor = -1;
        if(i>0) neighbor = arr[i-1][j].type;
        if(j>0 && (rand() % 2)) neighbor = arr[i][j-1].type;
        // 80%���ʺ��ھ�һ����20%����
        if(neighbor!=-1 && rand()%10<8)
            t = neighbor;
        else
            t = randint(0,2);
    }
    return t; 
} 

void setRandomEarth()
{
	for(int i=0;i<Height;i++) {
        for(int j=0;j<Width;j++) {
            int t = getRandomType(i, j);
            arr[i][j].type = t;
            arr[i][j].pic = get_pic(t);
            
        }
        cout << endl;
    }
}

void render() {
    for(int i=0;i<Height;i++) {
        for(int j=0;j<Width;j++) {
            if ( i == player.y && j == player.x)
            {
            	cout << player.pic;
			}
			else
			{
				cout << arr[i][j].pic;
			}
            
        }
        cout << endl;
    }
}

void clear()
{
	for (int i = 0; i < 20;i++)
	{
		cout << endl;
	}
}

void move()
{
    string s;
    cin >> s;
    char x = s[0];
    int new_x = player.x;
    int new_y = player.y;

    // ������Ҫȥ��������
    if (x == 'w')
        new_y = player.y - 1;
    if (x == 's')
        new_y = player.y + 1;
    if (x == 'a')
        new_x = player.x - 1;
    if (x == 'd')
        new_x = player.x + 1;

    // �߽��ж�
    if (new_x < 0 || new_x >= Width || new_y < 0 || new_y >= Height) {
        cout << "��ײǽ����" << endl;
        return; // ���ƶ�
    }

    // ˮ�ж�
    if (arr[new_y][new_x].type == 1) { // type==1��ˮ
        cout << "������ˮ������ͨ����" << endl;
        return; // ���ƶ�
    }

    // �����ƶ���
    player.x = new_x;
    player.y = new_y;
}


int main() {
    srand(time(0));
    
    setRandomEarth();
    
    while (true)
    {
    	clear();
    	render();
		move();
	}
   
    
   
    
    return 0;
}

