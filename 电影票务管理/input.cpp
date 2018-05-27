#include"include.h"


void goto_xy(int x, int y);//光标定位函数

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

int jiantou_max(void)
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
			case 75:return 3;
			case 77:return 4;
			default:continue;
			}
		}
	}
	return 0;
}
//上下左右箭头的获取


int choose_yn(void)
{

	char ch;
	ch = getch();
	do {
		if (ch != '\r'&&ch != '\x1b')
		{
			goto_xy(10, 28);
			printf("警告：输入错误！\a  请输入[Enter] 或 [Esc]！ ");
			ch = getch();
		}
	} while (ch != '\r'&&ch != '\x1b');

	if (ch == '\r')
		return 1;
	else if (ch == '\x1b')
		return 0;
}
//获取是或否

int choose_ayn(void)
{
	char ch;
	ch = getch();
	do {
		if (ch != '\r'&&ch != '\x1b'&&ch != '*')
		{
			goto_xy(10, 28);
			printf("警告：输入错误！\a  请输入[Enter] 或 [Esc] 或 [*]！ ");
			ch = getch();
		}
	} while (ch != '\r'&&ch != '\x1b'&&ch != '*');

	if (ch == '\r')
		return 1;
	else if (ch == '\x1b')
		return 0;
	else if (ch == '*')
		return 2;
}
//获取是或否或星号


char* input_add_back(void)
{
	char name[18];
	char ch;
	int  i = 0;
	while ((ch = getch()) != '\r')
	{
		if (ch < 0)
		{
			getch();
			continue;
		}
		if (ch == '\x1b')
		{
			strcpy(name, "!#%&(");
			return name;
		}
		else if (ch == 8 && i > 0)
		{
			printf("\b \b");
			i--;
			continue;
		}
		else if (ch != 8 && i < 10)
		{
			printf("%c", ch);
			name[i] = ch;
			i++;
		}
	}
	name[i] = '\0';
	return name;
}
//用户名特殊登录

char* input_pass_back(void)
{
	char pass[18];
	char ch;
	int  i = 0;
	while ((ch = getch()) != '\r')
	{
		if (ch < 0)
		{
			getch();
			continue;
		}
		if (ch == '\x1b')
		{
			strcpy(pass, "!#%&(");
			return pass;
		}
		else if (ch == 8 && i > 0)
		{
			printf("\b \b");
			i--;
			continue;
		}
		else if (ch != 8 && i < 16)
		{
			printf("*");
			pass[i] = ch;
			i++;
		}
	}
	pass[i] = '\0';
	return pass;
}
//密码特殊获取



int place_view_choose(void)
{
	char ch;
	while (ch = getch(), ch != '\x1b'&&ch != '+' && ch != '-' && ch != '*'&& ch != '/')
	{
		if (ch < 0)
		{
			ch = getch();
			switch (ch)
			{
			case 72:return 1;
			case 80:return 2;
			case 75:return 6;
			case 77:return 7;
			default:continue;
			}
		}
	}
	if (ch == '+')
		return 3;
	else if (ch == '-')
		return 4;
	else if (ch == '*')
		return 5;
	else if (ch == '/')
		return 8;

	return 0;
}
//场地选择

int place_empty_choose(void)
{
	char ch;
	while (ch = getch(), ch != '\x1b'&&ch != '+')
	{
		goto_xy(10, 28);
		printf("警告：请输入[Esc] 或 [+]                                                        ");
		continue;
	}

	if (ch == '+')
		return 1;
	else if (ch == '\x1b')
		return 0;
}
//空场地的选择

char* place_input(int x, int y)
{
	char name[18];
	char ch;
	int  i = 0;
	while ((ch = getch()) != '\r')
	{
		if (ch < 0)
		{
			getch();
			goto_xy(10, 28);
			printf("警告：只能输入数字！\a");
			goto_xy(x, y);
			continue;
		}
		if (ch == '\x1b')
		{
			strcpy(name, "!");
			return name;
		}
		if (ch == 8 && i > 0)
		{
			printf("\b \b");
			i--;
			continue;
		}
		if (!(ch >= '0'&&ch <= '9'))
		{
			goto_xy(10, 28);
			printf("警告：只能输入数字！\a");
			goto_xy(x, y);
			continue;
		}
		else if (ch != 8 && i < 3)
		{
			printf("%c", ch);
			name[i] = ch;
			i++;
		}
	}
	name[i] = '\0';
	return name;
}
//场地的输入


int input_jiantou_back(void)
{
	char ch;
	while (ch = getch(), ch != '\r'&&ch != '\x1b')
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
	if (ch == '\r')
		return 0;
	if (ch == '\x1b')
		return 3;
}
//上下箭头的获取加返回

char *movie_input(void)
{
	char name[35];
	int i = 0;
	
	fgets(name, 35, stdin);
	
	while (name[i] != '\n'&&name[i] != '\0')
		i++;
	if (name[i] == '\n')
		name[i] = '\0';
	else
		while (getchar() != '\n')
			continue;

	return name;
}
//电影信息获取
