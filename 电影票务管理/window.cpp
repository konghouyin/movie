#include"include.h"


void goto_xy(int x, int y) {				
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}
//定位光标位置到指定坐标



void kuangjia(void)
{
	printf("\n\t-----------------------------------------------------------------------------------------------------");
	printf("\n\t*                                    电 影 院 票 务 管 理 系 统                                     *");
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
//基本模版

void door(void)//开始门户，欢迎界面
{
	int i;
	int j;
	printf("\n\t                                                  ");//起始位置

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
	printf("电 ");
	Sleep(200);
	printf("影 ");
	Sleep(200);
	printf("院 ");
	Sleep(200);
	printf("票 ");
	Sleep(200);
	printf("务 ");
	Sleep(200);
	printf("管 ");
	Sleep(200);
	printf("理 ");
	Sleep(200);
	printf("系 ");
	Sleep(200);
	printf("统");
	Sleep(200);
	
	goto_xy(10, 3);
	printf("--------------------------------------------------------------------------------------------------");
	Sleep(1000);


	goto_xy(75, 21);
	printf("制作 : konghouyin");
	goto_xy(75, 23);
	printf("测试 : 2018 / 04 / 26");
	goto_xy(75, 25);
	printf("版本号 : V3.2.2");
	Sleep(500);

	goto_xy(50, 12);
	printf("系统正在启动...");
	Sleep(500);




	goto_xy(35, 14);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("▋ ▋ ");
		Sleep(rand() % 400+500);
	}
}
//登录欢迎界面

void end(void)
{
	clrscr();
	kuangjia();
	goto_xy(50, 13);
	printf("系统正在退出...");
	Sleep(500);

	int i;
	goto_xy(35, 15);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("▋ ▋ ");
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
//程序退出

void save_time(void)
{
	clrscr();
	kuangjia();
	goto_xy(50,13);
	printf("信 息 正 在 存 储");
	int i;
	goto_xy(35, 16);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("▋ ▋ ");
		Sleep(rand() % 200 + 200);
	}

}
//储存延时动画


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
	printf("恭喜");
	goto_xy(53, 15);
	printf("你已经成功注册");
	goto_xy(51, 17);
	printf("3秒后将返回主菜单！");
	goto_xy(0, 0);

	return;
}
//注册成功

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
	printf("\a警告");
	goto_xy(51, 14);
	printf("注册过程出现异常");
	goto_xy(46, 16);
	printf("请重试，或联系管理员寻求帮助");
	goto_xy(51, 18);
	printf("3秒后将返回主菜单！");
	goto_xy(0, 0);

	return;
}
//注册失败



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
	COORD coordScreen = { 0,0 };//设置清屏后光标返回的屏幕左上角坐标
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;//保存缓冲区信息
	DWORD dwConSize;//当前缓冲区可容纳的字符数
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);//获得缓冲区信息
	PERR(bSuccess, "GetConsoleScreenBufferInfo");
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;//缓冲区容纳字符数目
											  //用空格填充缓冲区
	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputCharacter");
	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);//获得缓冲区信息
	PERR(bSuccess, "ConsoleScreenBufferInfo");
	//填充缓冲区属性
	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputAttribute");
	//光标返回屏幕左上角坐标
	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");
	return;
}
//定义clrscr()