#include"include.h"






void goto_xy(int x, int y);//跳转
void kuangjia(void);//进本框架
void save_time(void);//存储延时


int place_empty_choose(void);//空场地的选择
int place_view_choose(void);//场地修改的选择
void list_place_input(void);//添加场地信息
char* place_input(int x,int y);//场地信息获取输入
void list_place_end(place* p);//结束输入并确认
int choose_yn(void);//获取是或否
void list_place_star(int x, int y);//打印星号
int list_place_delete_choose(place *p);//删除信息的确认



int place_chongfu(int n)
{
	place *pl;
	FILE *pln;
	pln = fopen("pln.txt", "a+");
	if (NULL == pln)
	{
		clrscr();
		kuangjia();
		goto_xy(56, 13);
		printf("Wrong!");
		goto_xy(43, 16);
		fprintf(stdout, "系统文件已损坏，请联系管理员！\a");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}

	pl = (place*)malloc(sizeof(place));
	while (fread(pl, sizeof(place), 1, pln) == 1)
	{
		if (n == pl->num)
			return 1;
	}
	return 0;
}
//进行影厅的查重

place* open_place(void)
{
	place *pl, *pl_head, *mid;
	pl_head = (place*)malloc(sizeof(place));
	pl_head->next = NULL;
	mid = pl_head;

	FILE *pln;
	pln = fopen("pln.txt", "a+");
	if (NULL == pln)
	{
		clrscr();
		kuangjia();
		goto_xy(56, 13);
		printf("Wrong!");
		goto_xy(43, 16);
		fprintf(stdout, "系统文件已损坏，请联系管理员！\a");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	pl = (place*)malloc(sizeof(place));
	while (fread(pl, sizeof(place), 1, pln) == 1)
	{
		mid->next = pl;
		pl->next = NULL;
		mid = pl;
		pl = (place*)malloc(sizeof(place));
	}
	free(pl);
	return pl_head;
}
//场地文件打开


void save_place(place* pl)
{
	FILE *pln;
	pln = fopen("pln.txt", "w");
	if (pln == NULL)
	{
		clrscr();
		kuangjia();
		goto_xy(56, 13);
		printf("Wrong!");
		goto_xy(43, 16);
		fprintf(stdout, "系统文件已损坏，请联系管理员！\a");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	else
	{
		pl = pl->next;
		while (fwrite(pl, sizeof(place), 1, pln) == 1)
		{
			pl = pl->next;
			if (pl == NULL)
				break;
		}
	}
	fflush(pln);
	save_time();
	return;
}
//场地文件的存储


void output_place(place* pl)
{
	place *p, *pn;

	int i, j, n = 0;
	for (p = pl; p != NULL; p = p->next)
	{
		n++;
	}

	for (i = 0; i < n - 2; i++)
	{
		p = pl;
		for (j = 0; j < n - 2 - i; j++)
		{
			pn = p->next;
			if ((pn->num) >(pn->next->num))
			{
				p->next = p->next->next;
				pn->next = pn->next->next;
				p->next->next = pn;
			}
			p = p->next;
		}
	}


	clrscr();
	kuangjia();
	goto_xy(50, 6);
	printf("场 地 信 息 管 理");
	goto_xy(28, 8);
	printf("------------------------------------------------------------");
	goto_xy(31, 9);
	printf("选择       场地编号       行       列      可容纳人数");


	i = 11;
	for (p = pl->next; p != NULL; p = p->next)
	{
		goto_xy(31, i);
		printf("             %2d           %2d       %2d           %3d", p->num,p->hang,p->lie ,p->site);
		i=i+2;
	}

	return;
}
//排序并打印相关的场地信息

int place_add(place *pl)
{
	char str[4];
	int flag_place;
	place *p;

	int n = 0;
	for (p = pl->next; p != NULL; p = p->next)
	{
		n++;
	}
	if (n >= 8)
	{
		clrscr();
		kuangjia();
		goto_xy(55,17);
		printf("Wrong!\a");
		goto_xy(50, 14);
		printf("影厅数以到达上限!");
		goto_xy(50, 17);
		printf("3秒后返回场地列表");
		Sleep(3000);

		return 0;
	}


	p = (place*)malloc(sizeof(place));

	while (1)
	{
		int flag_place_chongfu;
		list_place_input();
		goto_xy(55, 11);
		strcpy(str, place_input(55,11));
		if (strcmp(str, "!") == 0)
		{
			free(p);
			return 0;
		}
		sscanf(str, "%d", &p->num);
		flag_place_chongfu = place_chongfu(p->num);
		if (flag_place_chongfu == 1)
		{
			clrscr();
			kuangjia();
			goto_xy(55, 11);
			printf("Wrong!\a");
			goto_xy(50, 14);
			printf("输入影厅已经录入!");
			goto_xy(50, 17);
			printf("3秒后重新信息输入");
			Sleep(3000);
			continue;
		}
		goto_xy(55, 15);
		strcpy(str, place_input(55,15));
		if (strcmp(str, "!") == 0)
		{
			free(p);
			return 0;
		}
		sscanf(str, "%d", &p->hang);

		goto_xy(55, 19);
		strcpy(str, place_input(55, 19));
		if (strcmp(str, "!") == 0)
		{
			free(p);
			return 0;
		}			
		sscanf(str, "%d", &p->lie);

		list_place_end(p);
		goto_xy(0, 0);
		flag_place = choose_yn();
		if (flag_place == 1)
			break;
	}
	p->site = p->hang*p->lie;
	p->next = pl->next;
	pl->next = p;
	return 1;
}
//场地的添加

int place_delete(place *pl, int n)
{
	place *p,*q;
	q = pl;
	for (int i = 1; i < n; i++)
	{
		q = q->next;
	}
	p = q->next;
	int flag_place_delete = list_place_delete_choose(p);
	if (flag_place_delete == 1)
	{
		q->next = q->next->next;
		free(p);
		return 1;
	}
	else
		return 0;
}
//场地的删除

int place_change(place *pl, int n)

{
	place *p,*mid;
	mid = (place*)malloc(sizeof(place));
	p = pl;
	for (int i = 0; i < n; i++)
	{
		p = p->next;
	}
	
	char str1[4];
	char str2[4];
	char str3[4];

	while(1)
	{
		int flag_place_chongfu;
		list_place_input();
		goto_xy(55, 11);
		strcpy(str1, place_input(55, 11));
		if (strcmp(str1, "!") == 0)
		{
			free(mid);
			return 0;
		}
		sscanf(str1, "%d", &mid->num);


		flag_place_chongfu = place_chongfu(mid->num);
		if (flag_place_chongfu == 1 && mid->num!=p->num)
		{
			clrscr();
			kuangjia();
			goto_xy(55, 10);
			printf("Wrong!\a");
			goto_xy(43, 13);
			printf("新输入的场地信息与之前输入的冲突！");
			goto_xy(50, 16);
			printf("3秒后重新信息输入");
			Sleep(3000);
			continue;
		}

		goto_xy(55, 15);
		strcpy(str2, place_input(55, 15));
		if (strcmp(str2, "!") == 0)
		{
			free(mid);
			return 0;
		}
		sscanf(str2, "%d", &mid->hang);

		goto_xy(55, 19);
		strcpy(str3, place_input(55, 19));
		if (strcmp(str3, "!") == 0)
		{
			free(mid);
			return 0;
		}
		sscanf(str3, "%d", &mid->lie);

		list_place_end(mid);
		goto_xy(0, 0);
		int flag_place = choose_yn();
		if (flag_place == 1)
			break;
	}
	sscanf(str1, "%d", &p->num);
	sscanf(str2, "%d", &p->hang);
	sscanf(str3, "%d", &p->lie);
	p->site = p->hang*p->lie;
	
	free(mid);
	return 1;

}
//场地信息的修改

void place_manage(void)
{
	place *head;

place_jump:head = open_place();
	if (head->next == NULL)
	{
		clrscr();
		kuangjia();
		goto_xy(50, 10);
		printf("场 地 信 息 管 理");
		goto_xy(41, 15);
		printf("没有任何场地信息，按 [+] 添加新的场地");
		goto_xy(50, 18);
		printf("按 [Esc] 返回菜单");

		int flag_empty_place;
		goto_xy(16, 28);
		printf("没有任何场地信息，按 [+] 添加新的场地                                      ");
		flag_empty_place = place_empty_choose();

		if (flag_empty_place == 0)//释放malloc
		{
			return;
		}
		else if (flag_empty_place == 1)
		{
			if(place_add(head))
				save_place(head);//释放malloc
			goto place_jump;
		}
	}
	else
	{
		int flag_place;

		output_place(head);
		goto_xy(20, 28);
		printf("↑↓  选择      按[+] 增加     [-] 删除       [*] 修改      [Esc] 返回     ");
		

		int n = 0;//表示链表中的节点个数
		place *p;
		for (p = head->next; p != NULL; p = p->next)
		{
			n++;
		}

		int i=11;
		list_place_star(31, i);
		flag_place = place_view_choose();

		while (1)
		{
			if (flag_place == 3)//加
			{
				if (place_add(head))
					save_place(head);//释放malloc
				goto place_jump;
			}
			else if (flag_place == 4)//删除
			{
				if(place_delete(head, (i - 9) / 2))
					save_place(head);//释放malloc
				goto place_jump;
			}
			else if (flag_place == 5)//修改
			{
				if (place_change(head, (i - 9) / 2))
					save_place(head);//释放malloc
				goto place_jump;
			}
			else if (flag_place == 0)//返回
			{
				return;
			}
			else if (flag_place == 1)//箭头向上
			{
				if (i > 11)
				{
					i -= 2;
				}
			}
			else if (flag_place == 2)//箭头向下
			{
				if (i < 9+2*n)
				{
					i += 2;
				}
			}
			list_place_star(31, i);
			flag_place = place_view_choose();
		}
	}
}
//场地管理