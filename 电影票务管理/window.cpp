#include"include.h"


void goto_xy(int x, int y) {				
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}
//��λ���λ�õ�ָ������



void kuangjia(void)
{
	printf("\n\t-----------------------------------------------------------------------------------------------------");
	printf("\n\t*                                    �� Ӱ Ժ Ʊ �� �� �� ϵ ͳ                                     *");
	printf("\n\t*---------------------------------------------------------------------------------------------------*");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*                                                                                                   *");
	printf("\n\t*---------------------------------------------------------------------------------------------------*");
	printf("\n\t*                                                                                                   *");
	printf("\n\t-----------------------------------------------------------------------------------------------------");
}
//����ģ��

void door(void)//��ʼ�Ż�����ӭ����
{
	int i;
	int j;
	printf("\n\t                                                  ");//��ʼλ��

	for (i = 0; i < 101; )
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
	while (i < 27)
	{
		printf("\n\t*                                                                                                   *");
		Sleep(30);
		i++;
	}

	printf("\n\t                                                  ");
	for (i = 0; i < 51; i++)
	{
		goto_xy(8+i, 29);
		printf("-");
		goto_xy(108-i, 29);
		printf("-");
		Sleep(35);
	}

	Sleep(200);
	goto_xy(45,2);
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
	printf("--------------------------------------------------------------------------------------------------");
	Sleep(1000);


	goto_xy(75, 21);
	printf("���� : konghouyin");
	goto_xy(75, 23);
	printf("���� : 2018 / 04 / 26");
	goto_xy(75, 25);
	printf("�汾�� : V3.2.2");
	Sleep(500);

	goto_xy(50, 12);
	printf("ϵͳ��������...");
	Sleep(500);




	goto_xy(35, 14);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("�� �� ");
		Sleep(rand() % 400+500);
	}
}
//��¼��ӭ����

void end(void)
{
	clrscr();
	kuangjia();
	goto_xy(50, 13);
	printf("ϵͳ�����˳�...");
	Sleep(500);

	int i;
	goto_xy(35, 15);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("�� �� ");
		Sleep(rand() % 400 + 100);
	}
	
	for (i = 0; i < 53; i++)
	{
		goto_xy(60 - i, 29);
		printf(" ");
		goto_xy(60 + i, 29);
		printf(" ");
		goto_xy(60 - i, 28);
		printf(" ");
		goto_xy(60 + i, 28);
		printf(" ");
		goto_xy(60 - i, 27);
		printf(" ");
		goto_xy(60 + i, 27);
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
	for (i = 3; i < 16; i++)
	{
		goto_xy(0, i);
		printf("                                                                                                                   ");
		goto_xy(0, 29-i);
		printf("                                                                                                                   ");
		Sleep(45);      
	}
}
//�����˳�

void save_time(void)
{
	clrscr();
	kuangjia();
	goto_xy(50,13);
	printf("�� Ϣ �� �� �� ��");
	int i;
	goto_xy(35, 16);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("�� �� ");
		Sleep(rand() % 200 + 200);
	}

}
//������ʱ����


void right(void)
{
	clrscr();
	kuangjia();

	goto_xy(41, 11);
	printf("-------------------------------------");
	for (int i = 12; i < 19; i++)
	{
		goto_xy(41, i);
		printf("*                                   *");
	}
	goto_xy(41, 19);
	printf("-------------------------------------");

	goto_xy(57, 13);
	printf("��ϲ");
	goto_xy(53, 15);
	printf("���Ѿ��ɹ�ע��");
	goto_xy(51, 17);
	printf("3��󽫷������˵���");
	goto_xy(0, 0);

	return;
}
//ע��ɹ�

void wrong(void)
{
	clrscr();
	kuangjia();

	goto_xy(41, 10);
	printf("-------------------------------------");
	for (int i = 11; i < 20; i++)
	{
		goto_xy(41, i);
		printf("*                                   *");
	}
	goto_xy(41, 20);
	printf("-------------------------------------");

	goto_xy(57, 12);
	printf("\a����");
	goto_xy(51, 14);
	printf("ע����̳����쳣");
	goto_xy(46, 16);
	printf("�����ԣ�����ϵ����ԱѰ�����");
	goto_xy(51, 18);
	printf("3��󽫷������˵���");
	goto_xy(0, 0);

	return;
}
//ע��ʧ��



#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
void MyCls(HANDLE);
void clrscr(void)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	MyCls(hStdOut);
	return;
}
void MyCls(HANDLE hConsole)
{
	COORD coordScreen = { 0,0 };//�����������귵�ص���Ļ���Ͻ�����
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;//���滺������Ϣ
	DWORD dwConSize;//��ǰ�����������ɵ��ַ���
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);//��û�������Ϣ
	PERR(bSuccess, "GetConsoleScreenBufferInfo");
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;//�����������ַ���Ŀ
											  //�ÿո���仺����
	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputCharacter");
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);//��û�������Ϣ
	PERR(bSuccess, "ConsoleScreenBufferInfo");
	//��仺��������
	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputAttribute");
	//��귵����Ļ���Ͻ�����
	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");
	return;
}
//����clrscr()