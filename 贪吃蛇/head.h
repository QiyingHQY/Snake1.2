#include<stdlib.h>
#include<ege.h>
#include<math.h>
#include <graphics.h>
#include<stdio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


//��������������
typedef struct LinkList
{
	int x, y, direction;
	struct LinkList *next;
}snak;
//���巽��
typedef struct Direction
{
	int x, y;
}dir;
//����ʳ��
typedef struct Food
{
	int x, y,z;
}food;


void mainloop();
int begin();
