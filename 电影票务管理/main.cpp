#include"include.h"

int list_main(void);//主菜单列表
void door(void);//程序启动
void end(void);//程序退出
void reg(void);//注册程序
void log(void);//登录相关信息


void gly_(void);//////////////////////////////////


int main(void)
{
	system("电影票务管理系统---V3.2.2");
	door();
	int flag_list;
	while (1)
	{
		flag_list = list_main();
		switch (flag_list)
		{
		case 1:	Sleep(200); log(); break;
		case 2:Sleep(200);reg(); break;
		case 3:end();
		}
	}
	gly_();
	
	return 0;
}