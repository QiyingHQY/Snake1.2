//===============================
//�������ƣ�̰����
//�����ˣ�������
//����ʱ�䣺2016.12.22
//�ϴ��޸�ʱ�䣺2017.2.11 20:53
//������������5
//===============================
#include"head.h"

//���ڳߴ�
#define Win_L 654
#define Win_H 509

int main(void)
{
	char ch;

	ege::setinitmode(ege::INIT_ANIMATION);
	// ͼ�γ�ʼ��
	ege::initgraph(Win_L, Win_H);
	// �������ʼ���������Ҫʹ��������Ļ�
	ege::randomize();
	// ������ѭ��
	
	if (!begin())
		mainloop();
	
	// �رջ�ͼ�豸
	ege::closegraph();
	return 0;
}

//��ʼ����
int begin()
{
	//��Ч
	mciSendString(TEXT("open SWITCH.WAV alias SWITCH"), NULL, 0, NULL);
	char ch;
	int x, y;
	x = 200;
	y = 1;

	while (is_run())
	{
		//����
		cleardevice();

		setcolor(EGERGB(0x40, 0xE0, 0xD0));

		//����
		setfillcolor(EGERGB(0xEE, 0x79, 0x42));
		bar(260, x, 370, 250);

		//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
		setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

		//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
		//����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
		setfont(48, 0, "����");

		//д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
		//Ҫʹ�������ʽ���ַ�����outtextrect
		//�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
		setbkmode(TRANSPARENT);
		outtextxy(240, 100, "̰����");
		outtextxy(270, 200, "��ʼ");
		outtextxy(270, 250, "�˳�");

		ch = getch();
		if (ch == 27 || (x == 300 && (ch == 13 || ch == 32)))
		{
			mciSendString(TEXT("close SWITCH"), NULL, 0, NULL);
			mciSendString(TEXT("open SWITCH.WAV alias SWITCH"), NULL, 0, NULL);
			mciSendString(TEXT("play SWITCH"), NULL, 0, NULL);
			Sleep(200);
			return 1;
		}
		else if (x == 200 && (ch == 13 || ch == 32))
		{
			mciSendString(TEXT("close SWITCH"), NULL, 0, NULL);
			mciSendString(TEXT("open SWITCH.WAV alias SWITCH"), NULL, 0, NULL);
			mciSendString(TEXT("play SWITCH"), NULL, 0, NULL);
			return 0;
		}
		else if (ch == 's'&&y == 1)
		{
			y = 2;
			x = 300;
		}
		else if (ch == 'w'&&y == 2)
		{
			y = 1;
			x = 200;
		}

	}
}