

#include<stdio.h>
#include<graphics.h>		//easyX ��ͷ�ļ�����װ
#include<conio.h>			//_getch()
#include<math.h>
#include<Windows.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define PI 3.1415926535897932384624
#define MAXSTAR 1024	
#define MAXMETEOR 300

//����ͼƬ����
IMAGE img1, img2, img3;
//����
struct Star
{
	int x, y;
	int speed;
	int color;
}star[MAXSTAR];
//����
struct Meteor
{
	int x, y;
	int speed;
	int style;
}meteor[MAXMETEOR];
//��ʼ������
void initStar(int i)
{
	star[i].x = rand() % 1200;
	star[i].y = rand() % 800;
	star[i].speed = rand() % 8;
	star[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

//�����ǲ����ƶ�����
void drawAndMoveStar(int i)
{
	//�����ص�
	putpixel(star[i].x, star[i].y, star[i].color);
	//�ƶ�
	star[i].x += star[i].speed;
	//�ƶ�����������
	if (star[i].x > 1200)
	{
		initStar(i);
		//�����ص�
		putpixel(star[i].x, star[i].y, star[i].color);
	}
}

//��ʼ������
void initMeteor(int i)
{
	meteor[i].x = rand() % 2200 - 1200;		//[0,2199]--->[-1200,1199]
	meteor[i].y = -400;
	meteor[i].speed = rand() % 40;
	meteor[i].style = rand() % 2;			//[0,1]
}

//�����ǣ���ʾͼƬ����
void drawMeteor(int i)
{
	for (i = 0; i < MAXMETEOR; i++)
	{
		if (meteor[i].style == 0)
		{
			putimage(meteor[i].x, meteor[i].y, &img1, SRCPAINT);	//����ͼ
		}
		if (meteor[i].style == 1)
		{
			putimage(meteor[i].x, meteor[i].y, &img2, SRCPAINT);	//����ͼ
		}
	}
}

//�ƶ�����
void moveMeteor(int i)
{
	for (i = 0; i < MAXMETEOR; i++)
	{
		meteor[i].x += meteor[i].speed;
		meteor[i].y += meteor[i].speed;
		//�����Ƶ���������
		if (meteor[i].x > 1200 || meteor[i].y > 800)
		{
			initMeteor(i);
		}
	}
}

//�������
void textPrint()
{
	for (int i = 0; i < 60; i++)
	{
		cleardevice();
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		//Բ�ĵ�λ�ã�600��300   �뾶150   
		int x = 600 + int(150 * sin(PI * 2 * i / 60));
		int y = 300 + int(150 * cos(PI * 2 * i / 60));
		outtextxy(x - 50, y - 100, "�������Ǿó�ʱ");
		settextstyle(i, 0, "������κ");
		outtextxy(x, y, "�����ڳ���ĺĺ");
		Sleep(50);
	}
	Sleep(1000);
	cleardevice();
	settextcolor(YELLOW); 
	outtextxy(250, 100, "��һ������  ��һ�˰���"); Sleep(2000);
	outtextxy(250, 200, "��һ������  ��һ�����"); Sleep(2000);
	outtextxy(250, 300, "дһ�־���  ��һ�γ���"); Sleep(2000);
	outtextxy(250, 400, "���㾡һ��  ��������");   Sleep(2000);
	outtextxy(500, 500, "----------�����xxx");
	Sleep(4000);
	cleardevice();
}

int main()
{
	//����ͼƬ
	loadimage(&img1, "1.jpg", 50, 50);
	loadimage(&img2, "2.jpg", 50, 50);
	srand((unsigned int)time(NULL));
	//����һ��ͼ�δ���
	HWND hwnd;
	hwnd = initgraph(1200, 800);
	ShowWindow(hwnd, 3);

	//��������
	mciSendString("open С����.mp3 alias MM", 0, 0, 0);
	mciSendString("play MM repeat", 0, 0, 0);

	//���ñ���ģʽ
	setbkmode(0);
	textPrint();
	int i;
	for (i = 0; i < MAXSTAR; i++)
	{
		initStar(i);
	}
	for (i = 0; i < MAXMETEOR; i++)
	{
		initMeteor(i);
	}
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		for (i = 0; i < MAXSTAR; i++)
		{
			drawAndMoveStar(i);
		}

		drawMeteor(i);
		moveMeteor(i);

		Sleep(100);
		EndBatchDraw();
	}
	_getch();		//Ϊ�˷�ֹ����
	//�ر�ͼ�λ���
	closegraph();
	return 0;
}

