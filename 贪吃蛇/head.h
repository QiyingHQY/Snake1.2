#include<stdlib.h>
#include<stdio.h>
#include<math.h>

//egeͷ�ļ�
#include<ege.h>
#include <graphics.h>

//micSendString��ý��APIͷ�ļ�
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


//��������������
typedef struct LinkList
{
	int x;
	int	y;
	int direction;
	struct LinkList *next;
	struct LinkList *prev;
}snak;
//���巽��
typedef struct Direction
{
	int x;
	int y;
}dir;

//����ʳ��
typedef struct Food
{
	int x;
	int y;
	int z;
}food;

//��Ϸ��ѭ��
void mainloop();
int begin();
