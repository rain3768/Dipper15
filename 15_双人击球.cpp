#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>

#define Ball_r 6
#define player_v 15
#define life_circle_r 5
#define recetangle_length 50
#define recetangle_width  5
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)//ʵ�ֶ��λͬʱ����

//��ҽṹ��
typedef struct player
{
	int left;
	int top;
	COLORREF life_color;
	int life_num;
}Player;

Player Player1{}, Player2{};

//С��ṹ��
typedef struct circle {
	int x;
	int y;
	int x_v;
	int y_v;
}Circle;

Circle Ball;

//��ʼ������
void startup()
{
	initgraph(640, 480);

	//���ñ���
	setbkcolor(WHITE);
	cleardevice();

	//�ָ���
	setlinestyle(PS_SOLID, 5);
	setlinecolor(BLACK);
	line(0, 25, 640, 25);
	
	BeginBatchDraw();
}

//�̶�������ɫ��ʾ
void setblockcolor(COLORREF color, int left,int top,int right,int bottom)
{
	setlinecolor(color);
	rectangle(left, top, right, bottom);
	setfillcolor(color);
	floodfill(left + 10, top + 10, color, 0);
}

//�жϼ�λ���ڹ̶������ƶ�
Player update_player1()
{
	if (KEY_DOWN(0x41))
		Player1.left -= player_v;
	if  (KEY_DOWN(0x53))
		Player1.top += player_v;
	if  (KEY_DOWN(0x57))
		Player1.top -= player_v;
	if  (KEY_DOWN(0x44))
		Player1.left += player_v;
	if  (Player1.left < 0)
		Player1.left = 0;
	if  (Player1.left > 240)
		Player1.left = 240;
	if  (Player1.top < 30)
		Player1.top = 30;
	if  (Player1.top > 430)
		Player1.top = 430;

	return Player1;
}
Player update_player2()
{
	if (KEY_DOWN(VK_LEFT))
		Player2.left -= player_v;
	if (KEY_DOWN(VK_DOWN))
		Player2.top += player_v;
	if (KEY_DOWN(VK_UP))
		Player2.top -= player_v;
	if (KEY_DOWN(VK_RIGHT))
		Player2.left += player_v;
	if (Player2.left > 635)
		Player2.left = 635;
	if (Player2.left < 390)
		Player2.left = 390;
	if (Player2.top < 30)
		Player2.top = 30;
	if (Player2.top > 430)
		Player2.top = 430;

	return Player2;
}

//����С��λ��
Circle update_Ball()
{
	Ball.x += Ball.x_v;
	Ball.y += Ball.y_v;
	//�ж�С���Ƿ񵽴�߽粢����
	if (Ball.y >= 480 - Ball_r)
	{
		Ball.y_v = -Ball.y_v;
		Ball.y = 480 - Ball_r;
	}
	else if (Ball.y <= 30 + Ball_r)
	{
		Ball.y_v = -Ball.y_v;
		Ball.y = 30 + Ball_r;
	}
	//�ж��Ƿ������
	else if (Ball.x <= Player1.left + recetangle_width + Ball_r &&
		(Ball.y + Ball_r >= Player1.top &&
			Ball.y + Ball_r <= Player1.top + recetangle_length))
	{
		Ball.x_v = -Ball.x_v;
		Ball.x = Player1.left + recetangle_width + Ball_r;
	}
	else if (Ball.x >= Player2.left - Ball_r &&
		(Ball.y + Ball_r >= Player2.top &&
			Ball.y + Ball_r <= Player2.top + recetangle_length))
	{
		Ball.x_v = -Ball.x_v;
		Ball.x = Player2.left - Ball_r;
	}
	//�ж����û�д��򲢼���ĳλ�������ֵ��ͬʱ�ٴ��������С��λ��
	else if (Ball.x < Ball_r)
	{
		clearrectangle(0, 0, 640, 25);
		Player1.life_num--;
		Player1.life_color = RGB(105, 0, 0);
		Ball.x = 245 + Ball_r + rand() % ((390 - Ball_r) - (245 + Ball_r) + 1);
		Ball.y = 30 + Ball_r + rand() % ((480 - Ball_r) - (30 + Ball_r) + 1);
	}
		
	else if (Ball.x > 634)
	{
		clearrectangle(0, 0, 640, 25);
		Player2.life_num--;
		Player2.life_color = RGB(105, 0, 0);
		Ball.x = 245 + Ball_r + rand() % ((390 - Ball_r) - (245 + Ball_r) + 1);
		Ball.y = 30 + Ball_r + rand() % ((480 - Ball_r) - (30 + Ball_r) + 1);
	}

	return Ball;
}

//���������ʾ
void life_show(int life_num,int start_x,int start_y,COLORREF color)
{
	setfillcolor(color);
	for (int i = 0; i < life_num; i++,start_x+=10)
	{
		solidcircle(start_x, start_y, life_circle_r);
	}
}

int main()
{	
	//�ڹ̶������������С�򣨳�ʼλ�ã�
	srand((unsigned)time(NULL));
	Ball.x = 245 + Ball_r + rand() % ((390 - Ball_r) - (245 + Ball_r) + 1);
	Ball.y =  30 + Ball_r + rand() % ((480 - Ball_r) - ( 30 + Ball_r) + 1);
	Ball.x_v = Ball.y_v = 6;
	startup();

	Player1.left =   0, Player1.top = 200, Player1.life_color = RGB(205, 0, 0), Player1.life_num = 3,
	Player2.left = 635, Player2.top = 200, Player2.life_color = RGB(205, 0, 0), Player2.life_num = 3;

	while (1)
	{
		FlushBatchDraw();
		clearrectangle(0, 30, 640, 480);

		//�����ƶ�����
		setblockcolor(RGB(152, 245, 255),	0, 30, 245, 480);//player1
		setblockcolor(RGB(255, 236, 139), 390, 30, 640, 480);//player2
		
		//����С��
		setfillcolor(BLACK);
		solidcircle(Ball.x, Ball.y, Ball_r);
		update_Ball();

		//�������
		setfillcolor(BLACK);
		solidrectangle(Player1.left, Player1.top, Player1.left + recetangle_width, Player1.top + recetangle_length);
		solidrectangle(Player2.left, Player2.top, Player2.left + recetangle_width, Player2.top + recetangle_length);
	
		//����������ƺ�Ѫ��
		outtextxy(5, 5, L"PLAYER1");
		outtextxy(635 - textwidth(L"PLAYER2"), 5, L"PLAYER2");

		//�жϼ�λ���벢����С��λ��
		update_player1();
		update_player2();
		update_Ball();

		Sleep(100);
	}

	EndBatchDraw();
	_getch();
	closegraph();
}