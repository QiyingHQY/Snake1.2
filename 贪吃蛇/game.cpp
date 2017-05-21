#include"head.h"

void face(int length, int max);
void pause();

//�������棺1��ײǽ��2����ʳ��3���¼�¼
void death1(int length, int max);

void death2(int length, int max);

void death3(int length, int max);

//�����
int myrand(int m)
{
	// randomf() ����һ�� 0 �� 1 ֮������������
	int i;
	i = (int)(randomf() * m) * 10 + 4;
	return i;
}

int myrand_num(int m)
{
	// randomf() ����һ�� 0 �� 1 ֮������������
	int i;
	i = (int)(randomf() * m);
	return i;
}


void mainloop()
{
	//��Ч
	//��ȡ��Ƶ�ļ�
	mciSendString(TEXT("open shengzhang.wav alias shengzhang"), NULL, 0, NULL);
	mciSendString(TEXT("open zhishi.wav alias zhishi"), NULL, 0, NULL);
	mciSendString(TEXT("open zhuangqiang.WAV alias zhuangqiang"), NULL, 0, NULL);
	mciSendString(TEXT("open shengli.mp3 alias shengli"), NULL, 0, NULL);

	FILE *fp;
	char key = 0, lmax[5];
	int  length, mid_direction[2], num1, num2, accelerate, max, speed, speed_max, *pt;
	int last_direction;
	int i, n, j, book[5], s_x[7] = { 260,250,240,230,220,210,200 };

	//��ȡ��߼�¼
	fp = fopen("data\\Save\\length_max.txt", "r");
	if (fp == NULL)
		max = 3;//����ʧ�����ʼ��߼�¼Ϊ3
	else
	{
		fscanf(fp, "%d", &max);
		fclose(fp);
	}


	length = 3;//�߳�

	//ʹnum1��0��1������Ծ
	num1 = 0;
	num2 = -1;

	speed_max = 280;//����ٶ�
	accelerate = 0;//���ٶ�


	//��ʼ������
	dir direction[5] = { {0},{-10,0},{0,10},{10,0},{0,-10} };
	//����ʳ��
	food food;
	food.z = 0;

	//��ʼ����
	snak node, *head, *tail, *p, *t;
	head = NULL;
	for (i = 0; i < length; i++)
	{
		p = (snak *)malloc(sizeof(snak));
		p->direction = 3;
		p->x = s_x[i] + 4;
		p->y = 254;
		p->next = NULL;
		p->prev = NULL;
		if (head == NULL)
			head = p;
		else
		{
			tail->next = p;
			p->prev = tail;
		}
		tail = p;
	}
	
	for (; is_run(); delay_fps(60))
	{
		if (accelerate != 0)
			delay_ms(300 - speed_max);
		else
			delay_ms(300 - length);

		accelerate = 0;
		key = NULL;

		// todo: �߼�����

		//�������ʳ��
		if (food.z == 0)
		{
			while (true)
			{
				i = 0;
				food.x = myrand(50);
				food.y = myrand(50);
				t = head;
				while (t != NULL)
				{
					if (t->x == food.x&&t->y == food.y)
						i = 1;
					t = t->next;
				}
				if (i == 0)
					break;
			}
			food.z = 1;
		}
		
		

		//�˻�����
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			case 'w':
				if (head->direction == 4)
					accelerate = 1;
				if (head->direction != 2)
				{
					last_direction = head->direction;
					head->direction = 4;
				}
				break;
			case 's':
				if (head->direction == 2)
					accelerate = 1;
				if (head->direction != 4)
				{
					last_direction = head->direction;
					head->direction = 2;
					
				}
				break;
			case 'a':
				if (head->direction == 1)
					accelerate = 1;
				if (head->direction != 3)
				{
					last_direction = head->direction;
					head->direction = 1;
					
				}
				break;
			case 'd':
				if (head->direction == 3)
					accelerate = 1;
				if (head->direction != 1)
				{
					last_direction = head->direction;
					head->direction = 3;
					
				}
				break;
			case 32:
				pause();
				getch();
				key = NULL;
				break;
			default:
				break;
			}
		}

		/*int n = 0;
		t = head;
		while (t != NULL)
		{
			t->x += direction[t->direction].x;
			t->y += direction[t->direction].y;
			if (t->prev != NULL)
			{
				if (t->prev->direction != t->direction&&n==0)
				{
					last_direction =t->direction;
					t->direction = t->prev->direction;
					n = 1;
				}
				else if(t->prev->direction == t->direction)
					n = 0;
			}
			t = t->next;
		}*/
	
		t = head;
		t->x += direction[t->direction].x;
		t->y += direction[t->direction].y;
		mid_direction[num1] = t->direction;
		t = t->next;
		while (t != NULL)
		{
			num2 *= -1;
			num1 += num2;
			if (t->next != NULL)
			{
				t->x += direction[t->direction].x;
				t->y += direction[t->direction].y;
				mid_direction[num1] = t->direction;
				num2 *= -1;
				num1 += num2;
				t->direction = mid_direction[num1];
				num2 *= -1;
				num1 += num2;
				t = t->next;
			}
			else
			{
				num2 *= -1;
				num1 += num2;
				t->x += direction[t->direction].x;
				t->y += direction[t->direction].y;
				t->direction = mid_direction[num1];
				t = t->next;
			}
		}


		//��β����
		if (head->x == food.x&&head->y == food.y)
		{
			p = (snak *)malloc(sizeof(snak));
			p->direction = tail->direction;
			if (tail->direction == 1)
			{
				p->x = tail->x + 10;
				p->y = tail->y;
			}
			else if (tail->direction == 2)
			{
				p->x = tail->x;
				p->y = tail->y - 10;
			}
			else if (tail->direction == 3)
			{
				p->x = tail->x - 10;
				p->y = tail->y;
			}
			else if (tail->direction == 4)
			{
				p->x = tail->x;
				p->y = tail->y + 10;
			}
			p->next = NULL;
			p->prev = NULL;
			tail->next = p;
			p->prev = tail;
			tail = p;
			food.z = 0;
			length++;
			
			mciSendString(TEXT("seek shengzhang to 0"), NULL, 0, NULL);//ʹ���ֱ�����ʱ��ͷ��ʼ
			mciSendString(TEXT("play shengzhang"), NULL, 0, NULL);//��������
		}

		//��ʳ����
		t = head;
		t = t->next;
		while (t != NULL)
		{

			if (head->x == t->x && head->y == t->y)
				head->x = 999;
			t = t->next;
		}

		//��������
		if (head->x < 4 || head->x + 10>504 || head->y < 3 || head->y + 10>505)
		{
			if (max < length)
			{
				
				mciSendString(TEXT("seek shengli to 0"), NULL, 0, NULL);
				mciSendString(TEXT("play shengli"), NULL, 0, NULL);
				max = length;
				death3(length, max);
			}
			else if (head->x == 999)
			{
				
				mciSendString(TEXT("seek zhishi to 0"), NULL, 0, NULL);
				mciSendString(TEXT("play zhishi"), NULL, 0, NULL);
				death2(length, max);
			}
			else
			{
				mciSendString(TEXT("seek zhuangqiang to 0"), NULL, 0, NULL);
				mciSendString(TEXT("play zhuangqiang"), NULL, 0, NULL);
				death1(length, max);
			}
			delay_ms(2000);
			getkey();

			//�浵
			fp = fopen("data\\Save\\length_max.txt", "w");
			fprintf(fp, "%d", max);
			fclose(fp);

			
			mciSendString(TEXT("seek SWITkey to 0"), NULL, 0, NULL);
			mciSendString(TEXT("play SWITkey"), NULL, 0, NULL);
			break;
		}

		//ESCǿ���˳�
		if (key == 27)
		{
			fp = fopen("length_max.txt", "w");
			fprintf(fp, "%d", max);
			fclose(fp);

			break;
		}


		// todo: ͼ�θ���
		//�������������µ�λ�û�ͼͼ��
		cleardevice();
		//��ӡ������
		face(length, max);
		//��ӡʳ��
		setfillcolor(WHITE);
		bar(food.x, food.y, food.x + 11, food.y + 11);
		//��ӡ��
		t = head;
		while (t != NULL)
		{
			setfillcolor(EGERGB(0x00, 0xBF, 0xFF));
			bar(t->x, t->y, t->x + 11, t->y + 11);
			t = t->next;
		}
	}

	//�ر���Ƶ�ļ�
	mciSendString(TEXT("close SWITkey"), NULL, 0, NULL);
	mciSendString(TEXT("close zhuangqiang"), NULL, 0, NULL);
	mciSendString(TEXT("close zhishi"), NULL, 0, NULL);
	mciSendString(TEXT("close shengli"), NULL, 0, NULL);
	mciSendString(TEXT("close shengzhang"), NULL, 0, NULL);
}

void face(int length, int max)
{
	// ���������ɫ��һ��Ϊͼ���ڲ���ɫ
	setcolor(EGERGB(0, 0xFF, 0));
	setfillcolor(EGERGB(0xFF, 0x0, 0x80));

	//����߿�
	bar(0, 0, 654, 4);
	bar(505, 0, 509, 509);
	bar(0, 0, 4, 509);
	bar(0, 505, 654, 509);
	bar(651, 0, 654, 509);

	//������ɫ
	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
	//����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
	setfont(24, 0, "����");

	//д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
	//Ҫʹ�������ʽ���ַ�����outtextrect
	//�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
	setbkmode(TRANSPARENT);
	outtextxy(545, 20, "̰����");
	setfont(22, 0, "����");
	char str[20];
	sprintf(str, "����:%d", length);//�������е�����д��str�ַ���
	outtextxy(550, 60, str);
	sprintf(str, "��ʷ��¼:%d", max);
	outtextxy(515, 100, str);

}
void death1(int length, int max)
{
	//����
	cleardevice();

	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
	//����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
	setfont(48, 0, "����");

	//д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
	//Ҫʹ�������ʽ���ַ�����outtextrect
	//�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
	setbkmode(TRANSPARENT);
	outtextxy(160, 100, "��ײ��ǽ����ͷ��");
	setfont(32, 0, "����");
	char str1[20], str2[20];
	sprintf(str1, "���ճ���:%d", length);
	outtextxy(220, 170, str1);
	sprintf(str2, "��ʷ��¼:%d", max);
	outtextxy(220, 220, str2);
}
void death2(int length, int max)
{
	int i;
	//����
	cleardevice();

	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
	//����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
	setfont(48, 0, "����");

	//д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
	//Ҫʹ�������ʽ���ַ�����outtextrect
	//�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
	setbkmode(TRANSPARENT);
	i = myrand_num(2);
	switch (i)
	{
	case 1:
		outtextxy(75, 100, ">_<��磬�Ǹ����Ƕ���!");
		break;
	default:
		outtextxy(120, 100, "���ţ�������Լ���");
		break;
	}


	setfont(32, 0, "����");
	char str[20];
	sprintf(str, "���ճ���:%d", length);
	outtextxy(220, 170, str);
	sprintf(str, "��ʷ��¼:%d", max);
	outtextxy(220, 220, str);
}
void death3(int length, int max)
{
	//����
	cleardevice();

	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
	//����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
	setfont(48, 0, "����");

	//д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
	//Ҫʹ�������ʽ���ַ�����outtextrect
	//�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
	setbkmode(TRANSPARENT);
	outtextxy(120, 120, "��ϲ�㴴�����¼�¼��");
	setfont(40, 0, "����");
	char str[20];
	sprintf(str, "��߼�¼:%d", max);
	outtextxy(220, 200, str);
}

//��ͣ
void pause()
{
	setcolor(EGERGB(0x7C, 0xFC, 0x00));

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
	//����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
	setfont(48, 0, "����");

	//д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
	//Ҫʹ�������ʽ���ַ�����outtextrect
	//�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
	setbkmode(TRANSPARENT);
	outtextxy(210, 120, "��ͣ");
	setfont(35, 0, "����");
	outtextxy(160, 180, "�����������");
}
