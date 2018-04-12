#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include "header.h"

using namespace std;

int food[2] = { 9, 9 };		//food
static int ch = 0;
int headX, headY;			//snake's head
int speed = 500;			//speed
int score = 0;				//point
int level = 1;				//grade
LinkQueue snake;

void gotoxy(short x, short y);//移动光标
int setdirection(int x);//确定方向变量
void changesnake(int x);//改变蛇身坐标
void ifchangefood();//判断蛇是否吃到食物
void makefood();//创造新食物
bool is_die();//判断蛇是否存活
void drawsnake();//画蛇
void drawfood();//画食物
void drawwall();//画墙
void drawscore();//画数据
void draw();//绘图

int main()
{
	int po = 1;					//default direction
	InitQueue(snake);
	EnQueue(snake, 20, 20);		//default snake's head
	headX = snake.front->next->datax;
	headY = snake.front->next->datay;
	gotoxy(30, 5);
	cout << "欢迎来到贪吃蛇游戏";
	gotoxy(30, 7);
	cout << "作者：龙宇杰 版本1.1";
	gotoxy(30, 9);
	cout << "参考 https://github.com/HaloOrangeWang/BoringGames";
	gotoxy(30, 11);
	cout << "https://www.cnblogs.com/yonggandefeng/p/6233774.html";
	gotoxy(30, 13);
	cout << "https://github.com/bystc/Snake-c";
	gotoxy(30, 15);
	cout << "https://blog.csdn.net/silence1772/article/details/55005008"
	gotoxy(30, 17);
	cout << "按回车键继续...";
	cin.get();
	system("cls");
	gotoxy(30, 7);
	cout << "游戏控制方式:";
	gotoxy(30, 9);
	cout << "W键:向上 S键:向下";
	gotoxy(30, 11);
	cout << "A键:向左 D键:向右";
	gotoxy(30, 13);
	cout << "其它键:暂停";
	gotoxy(30, 17);
	cout << "按回车键开始游戏...";
	cin.get();
	system("cls");
	while (true)
	{
		po = setdirection(po);
		system("cls");
		changesnake(po);
		ifchangefood();
		if (is_die())
			break;
		draw();
		Sleep(speed);
	}
	DestroyQueue(snake);
	gotoxy(30, 10);
	cout << "Game Over!!!";
	Sleep(200);
	gotoxy(28, 12);
	system("pause");
	return 0;
}

void gotoxy(short x, short y)//change the cursor
{
	COORD position = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, position);
}

int setdirection(int x)
{
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
		case 'w':
			x = 1;
			break;
		case 's':
			x = 2;
			break;
		case 'a':
			x = 3;
			break;
		case 'd':
			x = 4;
			break;
		default:
			gotoxy(10, 16);
			cout << "游  戏  暂  停. . .";
			gotoxy(10, 18);
			system("pause");
			break;
		}
	}
	return x;
}

void changesnake(int x)
{
	switch (x)
	{
	case 1:
		headY -= 1;
		break;
	case 2:
		headY += 1;
		break;
	case 3:
		headX -= 1;
		break;
	case 4:
		headX += 1;
		break;
	default:
		break;
	}
	EnQueue(snake, headX, headY);
	(ch == 1) ? DeQueue(snake) : ch = 1;
}

void ifchangefood()
{
	if (snake.rear->datax == food[0] && snake.rear->datay == food[1])
	{
		ch = 0;
		int length = QueueLength(snake);
		makefood();
		++score;
		if (length > 5)
		{
			speed = 450;
			level = 2;
		}
		if (length > 30)
		{
			speed = 200;
			level = 3;
		}
		if (length > 50)
		{
			speed = 50;
			level = 4;
		}
		if (length > 100)
		{
			speed = 10;
			level = 5;
		}
	}
}

void makefood()
{
	srand((unsigned)time(NULL));
	food[0] = rand() % 30 + 2;
	food[1] = rand() % 30 + 4;
}

bool is_die()
{
	int length = QueueLength(snake);
	QueuePtr s = snake.front->next;
	for (int x = 1; x < length; ++x)
	{
		if (headX == s->datax && headY == s->datay)
		{
			return 1;
		}
		s = s->next;
	}
	if (headX < 1 || headY < 3 || headX > 34 || headY > 34)
		return 1;
	else
		return 0;
}

void drawsnake()
{
	gotoxy(snake.rear->datax, snake.rear->datay);
	cout << "h";
	int length = QueueLength(snake);
	QueuePtr s = snake.front->next;
	for (int n = 1; n < length; ++n)
	{
		gotoxy(s->datax, s->datay);
		cout << "n";
		s = s->next;
	}
}

void drawfood()
{
	gotoxy(food[0], food[1]);
	cout << "o";
}

void drawwall()
{
	gotoxy(0, 0);
	cout << "------------------------------------";
	gotoxy(0, 35);
	cout << "------------------------------------";
	for (int x = 0; x < 35; ++x)
	{
		gotoxy(0, x);
		cout << "|";
		gotoxy(35, x);
		cout << "|";
	}
}

void drawscore()
{
	gotoxy(37, 10);
	cout << "分数：" << score;
	gotoxy(37, 12);
	cout << "等级：" << level;
}

void draw()
{
	drawsnake();
	drawfood();
	drawwall();
	drawscore();
}