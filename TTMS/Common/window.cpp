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
//定位光标位置到指定坐标

void kuangjia(void)
{
	printf("\n\t------------------------------------------------------------------------------------------------------------");
	printf("\n\t*                                        电 影 院 票 务 管 理 系 统                                         *");
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
//基本模版


void door(void)//开始门户，欢迎界面
{
	int i;
	int j;
	printf("\n\t                                                      ");//起始位置

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
	printf("---------------------------------------------------------------------------------------------------------");
	Sleep(1000);


	goto_xy(80, 22);
	printf("制作 : 129号代码工厂");
	goto_xy(80, 24);
	printf("测试 : 2018 / 06 / 27");
	goto_xy(80, 26);
	printf("版本号 : V7.2.3");
	Sleep(500);


	goto_xy(55, 12);
	printf("系统正在启动...");
	Sleep(500);




	goto_xy(39, 15);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("▋ ▋ ");
		Sleep(rand() % 400 + 500);
	}
}
//登录欢迎界面

void end(void)
{
	int i, j, k;
	for (i = 6; i <= 30; i++)
	{
		goto_xy(9, i);
		printf("                                                                                                          ");
	}

	goto_xy(56, 12);
	printf("系统正在关闭...");

	Sleep(500);

	goto_xy(39, 15);
	srand(unsigned int(time(NULL)));
	for (i = 1; i <= 8; i++)
	{
		printf("▋ ▋ ");
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
//上下箭头的获取
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
//清除框框


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
//打印双线框框


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
		printf("选择此项目，可以登录系统，进行购票和信息查询。    ");
		goto_xy(0, 0);
	}
	else if (n == 2)
	{
		pt(43, 14);
		cls(43, 10);
		cls(43, 18);
		goto_xy(16, 30);
		printf("选择此项目，查看开发人员信息。                  ");
		goto_xy(0, 0);
	}
	else if (n == 3)
	{
		pt(43, 18);
		cls(43, 10);
		cls(43, 14);
		goto_xy(16, 30);
		printf("选择此项目，可以安全退出软件。                        ");
		goto_xy(0, 0);
	}
}
//主菜单打印转换

int list_main(void)
{
	int choose = 1;
	int jt;
	system("cls");
	kuangjia();
	goto_xy(23, 6);
	printf("请选择功能： ");
	goto_xy(50, 11);
	printf("1.登录");
	goto_xy(48, 15);
	printf("2.开发人员");
	goto_xy(50, 19);
	printf("3.退出");
	goto_xy(70, 25);
	printf("↑↓  选择     [Enter]   确认");
	goto_xy(10, 30);
	printf("说明：");



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
//主菜单及选择


void programer(void)
{
	system("cls");
	kuangjia();
	goto_xy(0, 5);
	printf("\t\t\t\t\t\t开发人员名单及分工\n\n\n");

	printf("\t\t\t04173167	樊宗渤    组长	    统计销售额，统计票房，维护个人资料，管理系统用户\n\n"
		   "\t\t\t04173162	陈健源	  副组长    售票，退票\n\n"
		   "\t\t\t04173164	周弋翕	  组员	    安排演出\n\n"
		   "\t\t\t04173165	雷新钰	  组员      查询演出，查询演出票\n\n"
		   "\t\t\t04173166	张箫	  组员	    设置座位，管理剧目\n\n"
		   "\t\t\t04173163 	王晋华	  组员      生成演出票\n\n");

	getchar();
}

