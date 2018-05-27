#include"include.h"


void kuangjia(void);//基本模版
void goto_xy(int x, int y);//跳转函数
int jiantou(void);//箭头识别函数
void kuangjia(void);//基本模版
int choose_yn(void);//获取是或否
int jiantou_max(void);//上下左右箭头获取
int input_jiantou_back(void);//上下箭头加返回的获取
int choose_ayn(void);//获取是否和星号
char* u_encryption(char* p);//解密函数



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
	goto_xy(x, y+1);
	printf("||");
	goto_xy(x+19, y + 1);
	printf("||");
	goto_xy(x, y+2);
	printf("---------------------");
}
//打印双线框框

void pt_one(int x, int y)
{
	goto_xy(x, y);
	printf(" ---------------------");
	goto_xy(x, y + 1);
	printf("|");
	goto_xy(x + 19, y + 1);
	printf("   |");
	goto_xy(x, y + 2);
	printf(" ---------------------");
}
//打印单线框框





void pt_main(int n)
{
	if (n == 1)
	{
		pt(43, 10);
		cls(43, 14);
		cls(43, 18);
		goto_xy(16, 28);
		printf("选择此项目，可以登录系统，进行购票和信息查询。    ");
		goto_xy(0, 0);
	}
	else if (n == 2)
	{
		pt(43, 14);
		cls(43, 10);
		cls(43, 18);
		goto_xy(16, 28);
		printf("选择此项目，进行注册，享受相关服务。                  ");
		goto_xy(0, 0);
	}
	else if (n == 3)
	{
		pt(43, 18);
		cls(43,10);
		cls(43, 14);
		goto_xy(16, 28);
		printf("选择此项目，可以安全退出软件。                        ");
		goto_xy(0, 0);
	}
}
//主菜单打印转换

int list_main(void)
{
	int choose = 1;
	int jt;
	clrscr();
	kuangjia();
	goto_xy(23,6);
	printf("请选择功能： ");
	goto_xy(50,11); 
	printf("1.登录");
	goto_xy(50,15);
	printf("2.注册");
	goto_xy(50,19);
	printf("3.退出");
	goto_xy(70, 25);
	printf("↑↓  选择     [Enter]   确认");
	goto_xy(10,28);
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





int list_reg_choose(void)
{
	clrscr();
	kuangjia();
	goto_xy(53,8);
	printf("用户须知");
	Sleep(500);
	goto_xy(40,11);
	printf("1.注册后即可登录系统，享受相关服务");
	Sleep(500);
	goto_xy(40,13);
	printf("2.请牢记账号和密码，忘记需联系管理员");
	Sleep(500);
	goto_xy(40,15);
	printf("3.账号1-10位字符，密码8-16位字符");
	Sleep(500);
	goto_xy(40,17);
	printf("4.账号密码只接受常规字符 ");
	Sleep(800);
	goto_xy(35, 23);
	printf("[Enter]   下一步                 [Esc]   取消");
	goto_xy(0, 0);

	return choose_yn();
}
//告知用户相关条规，并确认

void list_reg_in(void)
{
	clrscr();
	kuangjia();
	goto_xy(55, 8);
	printf("注 册");
	
	goto_xy(40, 12);
	printf("账号：");
	pt_one(46, 11);

	goto_xy(40, 16);
	printf("密码：");
	pt_one(46, 15);

	goto_xy(40, 20);
	printf("密码：");
	pt_one(46, 19);

	goto_xy(45, 23);
	printf("提示：按 [Esc] 放弃注册");


}
//正式注册列表

void list_reg_end(void)
{
	clrscr();
	kuangjia();

	goto_xy(30,8);
	printf("请确认填写信息:");
	goto_xy(40,12);
	printf("账号 : ");
	goto_xy(40,15);
	printf("密码 : ");
	goto_xy(42, 17);
	printf("按 [*] 显示（隐藏）密码");
	goto_xy(36,22);
	printf("[Enter]  确认                [Esc]  返回");

}
//输入结束并确认

void list_reg_pass(void)
{
	clrscr();
	kuangjia();
	goto_xy(30, 8);
	printf("请输入管理员密码完成注册:");
	goto_xy(40, 14);
	printf("密码：");
	pt_one(46, 13);
	

}
//获取管理员密码




void list_log_in(void)
{
	clrscr();
	kuangjia();

	goto_xy(51, 9);
	printf("系 统 登 录");

	goto_xy(40, 13);
	printf("账号：");
	pt_one(46, 12);

	goto_xy(40, 17);
	printf("密码：");
	pt_one(46, 16);

	goto_xy(45, 21);
	printf("提示：按 [Esc] 即可返回");
}
//登录输入界面




void pt_gly(int n)
{
	if (n == 1)
	{
		pt(28,11);
		cls(62,11);
		cls(28,15);
		cls(62,15);
		cls(28, 19);
		cls(62, 19);
		goto_xy(16, 28);
		printf("选择此项目，可进行票务办理。             ");
		goto_xy(0, 0);
	}
	else if (n == 2)
	{
		pt(62, 11);
		cls(28,11);
		cls(28,15);
		cls(62,15);
		cls(28,19);
		cls(62, 19);
		goto_xy(16, 28);
		printf("选择此项目，可以管理所有注册用户。                      ");
		goto_xy(0, 0);
	}
	else if (n == 3)
	{
		pt(28, 15);
		cls(28,11);
		cls(62,11);
		cls(62,15);
		cls(28,19);
		cls(62, 19);
		goto_xy(16, 28);
		printf("选择此项目，进入电影编辑。                                  ");
		goto_xy(0, 0);
	}
	else if (n == 4)
	{
		pt(62, 15);
		cls(28,11);
		cls(28,15);
		cls(62,11);
		cls(28,19);
		cls(62, 19);
		goto_xy(16, 28);
		printf("选择此项目，进入场地编辑。                                   ");
		goto_xy(0, 0);
	}
	else if (n == 5)
	{
		pt(28, 19);
		cls(28, 11);
		cls(28, 15);
		cls(62, 11);
		cls(62, 15);
		cls(62, 19);
		goto_xy(16, 28);
		printf("选择此项目，显示电影票务相关的统计信息。                  ");
		goto_xy(0, 0);
	}

	else if (n == 6)
	{
		pt(62, 19);
		cls(28,11);
		cls(28,15);
		cls(62,11);
		cls(62,15);
		cls(28, 19);
		goto_xy(16, 28);
		printf("选择此项目，可安全退出登录。                        ");
		goto_xy(0, 0);
	}

}
//管理员打印转换

int list_gly(void)
{
	int choose = 1;
	int jt;

	clrscr();
	kuangjia();

	goto_xy(50, 7);
	printf("管 理 员 菜 单");

	goto_xy(33,12);
	printf("1.票务办理");

	goto_xy(67,12);
	printf("2.用户管理");

	goto_xy(33,16);
	printf("3.电影管理");

	goto_xy(67,16);
	printf("4.场地管理");

	goto_xy(33,20);
	printf("5.统计信息");

	goto_xy(67, 20);
	printf("6.退出登录");


	goto_xy(66, 25);
	printf("↑↓←→  选择     [Enter]   确认");


	pt_gly(1);
	jt = jiantou_max();
	while (jt != 0)
	{
		if (choose==1||choose==3||choose==5)
		{
			if (jt == 4)
			{
				choose++;
				goto bbtt;
			}
		}
		if (choose==2||choose==4||choose==6)
		{
			if (jt == 3)
			{
				choose--;
				goto bbtt;
			}
		}
		if (choose == 1 || choose == 2 || choose == 3 || choose == 4)
		{
			if (jt == 2)
			{
				choose += 2;
				goto bbtt;
			}
		}
		if (choose == 3 || choose == 4 || choose == 5 || choose == 6)
		{
			if (jt == 1)
			{
				choose -= 2;
				goto bbtt;
			}
		}
		bbtt:pt_gly(choose);
		jt = jiantou_max();
	}
	return choose;
}
//管理员菜单及选择




void list_place_input(void)
{
	clrscr();
	kuangjia();

	goto_xy(51, 7);
	printf("场 地 添 加");

	goto_xy(40, 11);
	printf("编号：");
	pt_one(46, 10);

	goto_xy(40, 15);
	printf("行数：");
	pt_one(46, 14);

	goto_xy(40, 19);
	printf("列数：");
	pt_one(46, 18);

	goto_xy(45, 23);
	printf("提示：按 [Esc] 即可返回");
}
//添加场地信息

void list_place_end(place *p)
{
	clrscr();
	kuangjia();

	goto_xy(40, 9);
	printf("请确认填写信息:");
	goto_xy(50, 12);
	printf("编号 :   %d",p->num);
	goto_xy(50, 15);
	printf("行数 :   %d",p->hang);
	goto_xy(50, 18);
	printf("列数 :   %d", p->lie);
	goto_xy(36, 24);
	printf("[Enter]  确认              [Esc]  重新填写");
	goto_xy(0, 0);
}
//结束输入并确认

int list_place_delete_choose(place *p)
{
	clrscr();
	kuangjia();

	goto_xy(35, 8);
	printf("请确认是否删除相关信息:");
	goto_xy(50, 11);
	printf("编号 :   %d", p->num);
	goto_xy(50, 14);
	printf("行数 :   %d", p->hang);
	goto_xy(50, 17);
	printf("列数 :   %d", p->lie);
	goto_xy(50, 20);
	printf("人数 :   %d", p->site);
	goto_xy(36, 24);
	printf("[Enter]  确认              [Esc]  返回");
	goto_xy(0, 0);

	if (choose_yn())
		return 1;
	else
		return 0;
}
//删除场地信息的确认

void list_place_star(int x, int y)
{
	goto_xy(x, y);
	printf("--->");
	int i;
	for (i = y - 2; i >= 11; i -= 2)
	{
		goto_xy(x, i);
		printf("    ");
	}
	for (i = y + 2; i <= 25; i += 2)
	{
		goto_xy(x, i);
		printf("    ");
	}
	goto_xy(0, 0);
	return;
}
//打印星号



void pt_people(int n)
{
	if (n == 1)
	{
		pt(47, 12);
		cls(47, 17);
		goto_xy(16, 28);
		printf("选择此项目，可进行注册用户的管理。                  ");
		goto_xy(0, 0);
	}
	else if (n == 2)
	{
		pt(47, 17);
		cls(47, 12);
		goto_xy(16, 28);
		printf("选择此项目，可以修改管理员密码。                      ");
		goto_xy(0, 0);
	}
}
//打印人物线框

int list_gly_people(void)//输入函数需要换，不能光是上下，还要考虑返回
{
	clrscr();
	kuangjia();

	goto_xy(30, 9);
	printf("请选择需要查看的信息:");
	goto_xy(55, 13);
	printf("用户");
	goto_xy(55, 18);
	printf("管理员");
	goto_xy(50, 25);
	printf("↑↓  选择     [Enter]   确认      [Esc]   返回");

	int choose = 1;
	int jt;

	pt_people(1);
	jt = input_jiantou_back();
	while (jt != 0 && jt !=3 )
	{
		if (jt == 2 && choose==1)
		{
			choose++;
		}
		else if (jt == 1 && choose ==2)
		{
			choose--;
		}
		pt_people(choose);
		jt = input_jiantou_back();
	}
	if (jt == 0)
		return choose;
	else
		return 0;
}
//打印用户信息选择菜单并选择


int list_gly_change_choose(Node *gly)
{
	int l = strlen(gly->password);
	char out[19];
	int i;
	for (i = 0; i < l; i++)
	{
		out[i] = '*';
	}
	out[l] = '\0';

	list_reg_end();
	goto_xy(30, 8);
	printf("是否需要修改管理员信息：");
	goto_xy(48, 12);
	printf("%s", gly->name);
	goto_xy(48, 15);
	printf("%s", out);
	int flag_out = 0;//判断当前显示明文还是暗纹

	int flag_choose_ayn;
	flag_choose_ayn = choose_ayn();
	while (1)
	{
		if (flag_choose_ayn == 2)
		{
			if (flag_out % 2 == 0)
			{
				goto_xy(48, 15);
				printf("%s", gly->password);
				flag_out++;
			}
			else
			{
				goto_xy(48, 15);
				printf("%s", out);
				flag_out++;
			}
		}
		else if (flag_choose_ayn == 1)
			return 1;
		else if (flag_choose_ayn == 0)
			return 0;
		flag_choose_ayn = choose_ayn();
		goto_xy(0, 0);
	}
}
//是否修改管理员信息

int list_people_delete_choose(Node_p *p)
{
	clrscr();
	kuangjia();

	char gd[19];
	strcpy(gd, p->password);
	goto_xy(35, 10);
	printf("请确认是否删除相关信息:");
	goto_xy(50, 13);
	printf("用户名 :   %s", p->name);
	goto_xy(50, 16);
	printf("密码 :   %s", u_encryption(gd));
	goto_xy(36, 24);
	printf("[Enter]  确认              [Esc]  返回");
	goto_xy(0, 0);

	if (choose_yn())
		return 1;
	else
		return 0;
}
//删除场地信息的确认



void list_people_find(void)
{
	clrscr();
	kuangjia();

	goto_xy(51, 7);
	printf("用 户 查 询");

	goto_xy(40, 10);
	printf("账号：");
	pt_one(46, 9);

	goto_xy(50, 13);
	printf("按 [Esc] 返回");
	
}
//用户信息查询


void list_movie_add1(void)
{
	clrscr();
	kuangjia();

	goto_xy(48, 7);
	printf("电 影 信 息 添 加");

	goto_xy(40, 11);
	printf("名称：");

	goto_xy(40, 14);
	printf("时间：");

	goto_xy(40, 17);
	printf("金额：");

	goto_xy(40, 23);
	printf("电影类型：");

	goto_xy(30,25);
	printf("提示：按[Enter]确认输入无误，并开始填写下一项");
}
//添加电影信息