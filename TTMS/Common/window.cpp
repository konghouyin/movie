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
	printf("���� :129�Ŵ��빤��");
	goto_xy(80, 24);
	printf("���� : 2018 / 04 / 26");
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

void exit(void)
{
	int i, j, k;
	for (i = 6; i <= 30; i++)
	{
		goto_xy(0, i);
		printf("\t\t                                                      ");
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




