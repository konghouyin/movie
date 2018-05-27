#include"include.h"


int list_gly(void);//管理员菜单列表列表
void movie_manage(void);//电影内容管理
void place_manage(void);//场地信息管理
void people_manage(void);//用户信息管理


void gly_(void)
{
	int flag_gly;
	
	while (1)
	{	flag_gly=list_gly();
		switch (flag_gly)
		{
		case 1:
		case 2:Sleep(200); people_manage(); break;
		case 3:Sleep(200); movie_manage(); break;
		case 4:Sleep(200); place_manage(); break;
		case 5:
		case 6: return;
		}
	}
}
//管理员函数
