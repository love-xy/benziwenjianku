#include<stdio.h>
#include<graphics.h>
#define NUM 100
#include<conio.h>
#include<time.h>
#include<mmstream.h>
#pragma comment(lib,"winmm.lib")
//ö��
typedef enum Ch
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
}Ch;

typedef struct Coor
{
	int x;
	int y;//����
}Coor;

typedef struct Snake
{
	Ch ch;        //����
	int n;        //��
	Coor szb[NUM];    //ÿһ�ڵ�����
}Snake;

typedef struct Food
{
	int x, y;       //ʳ������
	bool isEat;              //�Ƿ񱻳Ե�
}Food;

Snake snake;
Food food;

void SnakeInit()
{
	srand((unsigned int)time(NULL));
	snake.ch = right;
	snake.n = 3;
	snake.szb[0].x = 320;
	snake.szb[0].y = 240;
	snake.szb[1].x = 310;
	snake.szb[1].y = 240;
	snake.szb[2].x = 300;
	snake.szb[2].y = 240;


	food.isEat = true;
}

void PrintSnake()
{
	printf("��ǰ�ߵķ���Ϊ��%d\n", snake.ch);
	printf("��ǰ�ߵĽ���Ϊ��%d\n", snake.n);
	for (int i = 0; i < snake.n; i++) {
		printf("��%d�ڵ���ߣ� x%d,y%d\n", i, snake.szb[i].x, snake.szb[i].y);
		rectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x + 10, snake.szb[i].y + 10);
	}
}

void SnackMove()
{
	for (int i = snake.n - 1; i > 0; i--) {
		snake.szb[i].x = snake.szb[i - 1].x;
		snake.szb[i].y = snake.szb[i - 1].y;
	}
	switch (snake.ch) {
	case up:snake.szb[0].y += 10;
		break;
	case down:snake.szb[0].y -= 10;
		break;
	case left:snake.szb[0].x -= 10;
		break;
	case right:snake.szb[0].x += 10;
		break;

	}
}

void ChangeSnakeCh(char key)
{
	key = getchar();
	switch (key) {
	case 'w':
	case up:
		if (snake.ch != down)
			snake.ch = up;
		break;
	case 's':
	case down:
		if (snake.ch != up)
			snake.ch = down;
		break;
	case 'd':
	case right:
		if (snake.ch != left)
			snake.ch = right;
		break;
	case left:
	case 'a':if (snake.ch != right)
		snake.ch = left;
		break;

	}
}

void xinshiwu()
{
	food.x = rand() % 64 * 10;
	food.y = rand() % 48 * 10;
	food.isEat = false;
}

void Drawfood()
{
	rectangle(food.x, food.y, food.x + 10, food.y + 10);
}

void Eatfood()
{
	if (snake.szb[0].x == food.x&&snake.szb[0].y == food.y)
	{
		snake.n++;
		food.isEat = true;
	}
}

void welcome()
{
	//loadimege(&backimg, L"321.jpg", 640, 480);
	//putimage(0, 0, &backing);

}

int main()
{
	char a;
	initgraph(640, 480, SHOWCONSOLE);
	mciSendString("open 111.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM", 0, 0, 0);


	SnakeInit();
	while (1) {
		system("cls");
		cleardevice();//�����Ļ'
		SnackMove();
		PrintSnake();
		if (a = _kbhit())
			ChangeSnakeCh(a);
		if (food.isEat == true)
			xinshiwu();
		Drawfood();
		Sleep(100);
	}
	return 0;
}