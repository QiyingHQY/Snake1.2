#include"head.h"

//��ʼ����
int begin()
{
	//��Ч
	mciSendString(TEXT("open data\\Music\\SWITkey.WAV alias SWITkey"), NULL, 0, NULL);//�򿪱�����Ƶ�ļ�
	char key;
	int y, mark;
	y = 200;
	mark = 1;

	while (is_run())
	{
		//����
		cleardevice();

		setcolor(EGERGB(0x40, 0xE0, 0xD0));

		//����
		setfillcolor(EGERGB(0xEE, 0x79, 0x42));
		bar(260, y, 370, 250);

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

		key = getch();
		if (key == 27 || (y == 300 && (key == 13 || key == 32)))
		{
			mciSendString(TEXT("seek SWITkey to 0"), NULL, 0, NULL);//�������Ž���
			mciSendString(TEXT("play SWITkey"), NULL, 0, NULL);//������Ƶ
			delay_ms(200);//�ӳ�200����
			return 1;
		}
		else if (y == 200 && (key == 13 || key == 32))
		{
			
			mciSendString(TEXT("seek SWITkey to 0"), NULL, 0, NULL);
			mciSendString(TEXT("play SWITkey"), NULL, 0, NULL);
			return 0;
		}
		else if (key == 's'&&mark == 1)
		{
			mark = 2;
			y = 300;
		}
		else if (key == 'w'&&mark == 2)
		{
			mark = 1;
			y = 200;
		}
	}

	mciSendString(TEXT("close SWITkey"), NULL, 0, NULL);
}