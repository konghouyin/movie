#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>

void goto_xy(int x, int y) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}
//��λ���λ�õ�ָ������

void kuangjia(void)
{
	printf("\n\t------------------------------------------------------------------------------------------------------------");
	printf("\n\t*                                        �� Ӱ Ժ Ʊ �� �� �� ϵ ͳ                                         *");
	printf("\n\t*-----------------------------------------------------------------------------------------------------------*");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t*                                                                                                           *");
	printf("\n\t-------------------------------------------------------------------------------------------------------------");
}
//����ģ��


void door(void)//��ʼ�Ż�����ӭ����
{
	int i;
	int j;
	printf("\n\t                                                      ");//��ʼλ��

	for (i = 0; i < 110; )
	{
		i++;
		for (j = 0; j < i; j++)
		{
			printf("-");
		}
		Sleep(35);
		i++;
		for (j = 0; j < i; j++)
			printf("\b");
	}

	i = 0;
	while (i < 29)
	{
		printf("\n\t*                                                                                                           *");
		Sleep(30);
		i++;
	}

	printf("\n\t                                                  ");
	for (i = 0; i < 55; i++)
	{
		goto_xy(8 + i, 31);
		printf("-");
		goto_xy(116 - i, 31);
		printf("-");
		Sleep(35);
	}

	Sleep(200);
	goto_xy(49, 2);
	printf("�� ");
	Sleep(200);
	printf("Ӱ ");
	Sleep(200);
	printf("Ժ ");
	Sleep(200);
	printf("Ʊ ");
	Sleep(200);
	printf("�� ");
	Sleep(200);
	printf("�� ");
	Sleep(200);
	printf("�� ");
	Sleep(200);
	printf("ϵ ");
	Sleep(200);
	printf("ͳ");
	Sleep(200);

	goto_xy(10, 3);
	printf("---------------------------------------------------------------------------------------------------------");
	Sleep(1000);


	goto_xy(80, 22);
	printf("���� : 129�Ŵ��빤��");
	goto_xy(80, 24);
	printf("���� : 2018 / 06 / 27");
	goto_xy(80, 26);
	printf("�汾�� : V7.2.3");
	Sleep(500);


	goto_xy(55, 12);
	printf("ϵͳ��������...");
	Sleep(500);




	goto_xy(39, 15);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("�� �� ");
		Sleep(rand() % 400 + 500);
	}
}
//��¼��ӭ����

void end(void)
{
	int i, j, k;
	for (i = 6; i <= 30; i++)
	{
		goto_xy(9, i);
		printf("                                                                                                          ");
	}

	goto_xy(56, 12);
	printf("ϵͳ���ڹر�...");

	Sleep(500);

	goto_xy(39, 15);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("�� �� ");
		Sleep(rand() % 400 + 500);
	}
	for (i = 0; i < 56; i++)
	{
		goto_xy(60 - i, 31);
		printf(" ");
		goto_xy(60 + i, 31);
		printf(" ");
		goto_xy(60 - i, 1);
		printf(" ");
		goto_xy(60 + i, 1);
		printf(" ");
		goto_xy(60 - i, 2);
		printf(" ");
		goto_xy(60 + i, 2);
		printf(" ");
		goto_xy(60 - i, 3);
		printf(" ");
		goto_xy(60 + i, 3);
		printf(" ");
		Sleep(35);
	}
	goto_xy(115, 2);
	printf("    ");
	goto_xy(115, 31);
	printf("    ");
	for (i = 3; i < 17; i++)
	{
		goto_xy(0, i);
		printf("                                                                                                                            ");
		goto_xy(0, 33 - i);
		printf("                                                                                                                           ");
		Sleep(45);
	}
	goto_xy(0, 0);

}

int jiantou(void)
{
	char ch;
	while (ch = getch(), ch != '\r')
	{
		if (ch < 0)
		{
			ch = getch();
			switch (ch)
			{
			case 72:return 1;
			case 80:return 2;
			default:continue;
			}
		}
	}
	return 0;
}
//���¼�ͷ�Ļ�ȡ
void cls(int x, int y)
{
	goto_xy(x, y);
	printf("                     ");
	goto_xy(x, y + 1);
	printf("   ");
	goto_xy(x + 19, y + 1);
	printf("   ");
	goto_xy(x, y + 2);
	printf("                     ");
	goto_xy(0, 0);
}
//������


void pt(int x, int y)
{
	goto_xy(x, y);
	printf("---------------------");
	goto_xy(x, y + 1);
	printf("||");
	goto_xy(x + 19, y + 1);
	printf("||");
	goto_xy(x, y + 2);
	printf("---------------------");
}
//��ӡ˫�߿��


void pt_main(int n)
{
	if (n == 1)
	{
		pt(43, 10);
		cls(43, 14);
		cls(43, 18);
		goto_xy(0, 29);
		printf("\t*-----------------------------------------------------------------------------------------------------------*");
		goto_xy(16, 30);
		printf("ѡ�����Ŀ�����Ե�¼ϵͳ�����й�Ʊ����Ϣ��ѯ��    ");
		goto_xy(0, 0);
	}
	else if (n == 2)
	{
		pt(43, 14);
		cls(43, 10);
		cls(43, 18);
		goto_xy(16, 30);
		printf("ѡ�����Ŀ���鿴������Ա��Ϣ��                  ");
		goto_xy(0, 0);
	}
	else if (n == 3)
	{
		pt(43, 18);
		cls(43, 10);
		cls(43, 14);
		goto_xy(16, 30);
		printf("ѡ�����Ŀ�����԰�ȫ�˳������                        ");
		goto_xy(0, 0);
	}
}
//���˵���ӡת��

int list_main(void)
{
	int choose = 1;
	int jt;
	system("cls");
	kuangjia();
	goto_xy(23, 6);
	printf("��ѡ���ܣ� ");
	goto_xy(50, 11);
	printf("1.��¼");
	goto_xy(48, 15);
	printf("2.������Ա");
	goto_xy(50, 19);
	printf("3.�˳�");
	goto_xy(70, 25);
	printf("����  ѡ��     [Enter]   ȷ��");
	goto_xy(10, 30);
	printf("˵����");



	pt_main(1);
	jt = jiantou();
	while (jt != 0)
	{
		if (jt == 2 && choose<3)
		{
			choose++;
		}
		else if (jt == 1 && choose > 1)
		{
			choose--;
		}
		pt_main(choose);
		jt = jiantou();
	}
	return choose;
}
//���˵���ѡ��


void programer(void)
{
	system("cls");
	kuangjia();
	goto_xy(0, 5);
	printf("\t\t\t\t\t\t������Ա�������ֹ�\n\n\n");

	printf("\t\t\t04173167	���ڲ�    �鳤	    ͳ�����۶ͳ��Ʊ����ά���������ϣ�����ϵͳ�û�\n\n"
		   "\t\t\t04173162	�½�Դ	  ���鳤    ��Ʊ����Ʊ\n\n"
		   "\t\t\t04173164	��߮��	  ��Ա	    �����ݳ�\n\n"
		   "\t\t\t04173165	������	  ��Ա      ��ѯ�ݳ�����ѯ�ݳ�Ʊ\n\n"
		   "\t\t\t04173166	����	  ��Ա	    ������λ�������Ŀ\n\n"
		   "\t\t\t04173163 	������	  ��Ա      �����ݳ�Ʊ\n\n");

	getchar();
}

