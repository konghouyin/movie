#include"include.h"


int list_gly_people(void);//打印修改信息选择菜单并选择
void gly_change(void);//管理员信息修改
Node* out_n(void);//管理员信息
int list_gly_change_choose(Node *gly);//是否修改管理员信息
char* u_encryption(char* p);//解密函数


void goto_xy(int x, int y);//光标跳转
void list_reg_in(void);//开始注册  打印相关输入列表
char* input_add_back(void);//字符串的获取
char* input_pass_back(void);//密码的获取
int pass_long(char* pass);//密码长度控制
void list_reg_end(void);//输入结束并确认
int choose_ayn(void);//获取 是或否或星号
Node *real_change(char *);//具体内容修改
char* encryption(char*);//加密函数
void save_time(void);//储存缓冲
void yh_change(void);//用户修改


void goto_xy(int x, int y);//跳转
void kuangjia(void);//框架
int place_empty_choose(void);//输入退出或加号
void list_place_star(int x, int y);//打印箭头
int place_view_choose(void);//增删改查功能选择
Node_p *real_change1(char *);//用户添加
int chongfu(char *name);//用户名查重
int list_people_delete_choose(Node_p *p);//人员删除确认
void list_people_find(void);//用户查找
int choose_yn(void);//获取是或否


void people_manage(void)
{
	int flag_people_list;
	while (1)
	{
		flag_people_list = list_gly_people();
		switch (flag_people_list)
		{
		case 1:Sleep(200); yh_change(); break;
		case 2:Sleep(200); gly_change(); break;
		case 0:Sleep(200); return;
		}
	}
}

Node_p* open_people(void)
{
	Node_p *pl, *pl_head, *mid;
	pl_head = (Node_p*)malloc(sizeof(Node_p));
	pl_head->next = NULL;
	mid = pl_head;

	FILE *pln;
	pln = fopen("midn.txt", "a+");
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
	pl = (Node_p*)malloc(sizeof(Node_p));
	while (fread(pl, sizeof(Node_p), 1, pln) == 1)
	{
		mid->next = pl;
		pl->next = NULL;
		mid = pl;
		pl = (Node_p*)malloc(sizeof(Node_p));
	}
	free(pl);
	return pl_head;
}
//人员文件打开

void people_save(Node_p *head)
{
	FILE *pln;
	pln = fopen("midn.txt", "w");
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
		head = head->next;
		while (fwrite(head, sizeof(Node_p), 1, pln) == 1)
		{
			head = head->next;
			if (head == NULL)
				break;
			strcpy(head->password,head->password);
		}
	}
	fflush(pln);
	save_time();
	return;
}
//人员的存储

void people_add(Node_p *head,Node_p *add)
{
	strcpy(add->password, encryption(add->password));
	Node_p *p;
	p = head->next;
	head->next = add;
	add->next = p;
	people_save(head);
	
}
//人员的添加

void output_people(Node_p* pl,int a,int b)
{
	Node_p *p;
	
	clrscr();
	kuangjia();
	goto_xy(14, 28);
	printf("↑↓ 选择   ←→ 翻页    [+]增加     [-]删除     [*]修改     [/]查找     [Esc]返回 ");

	goto_xy(50, 6);
	printf("人 员 信 息 管 理");
	goto_xy(32, 8);
	printf("----------------------------------------------------");
	goto_xy(35, 9);
	printf("选择             用户名                密码");

	int i = 11;
	for (p = pl; p != NULL && i<25; p = p->next)
	{
		char gd[19];
		strcpy(gd, p->password);

		goto_xy(35, i);
		printf("              %10s        %16s", p->name,u_encryption(gd));
		i = i + 2;
	}

	goto_xy(32, 25);
	printf("----------------   第%d页    共%d页   --------------- ", a, b);

	return;
}
//打印相关的人员信息

void list_people_star(int x, int y,int max)
{
	goto_xy(x, y);
	printf("--->");
	int i;
	for (i = y - 2; i >= 11; i -= 2)
	{
		goto_xy(x, i);
		printf("    ");
	}
	for (i = y + 2; i < max; i += 2)
	{
		goto_xy(x, i);
		printf("    ");
	}
	goto_xy(0, 0);
	return;
}
//打印星号

int people_delete(Node_p *pl, int n)
{
	Node_p *p, *q;
	q = pl;
	for (int i = 1; i < n; i++)
	{
		q = q->next;
	}
	p = q->next;
	int flag_place_delete = list_people_delete_choose(p);
	if (flag_place_delete == 1)
	{
		q->next = q->next->next;
		free(p);
		return 1;
	}
	else
		return 0;
}
//人员的删除

int people_change(Node_p *pl, int n)
{
	Node_p *p, *q,*change;
	q = pl;
	for (int i = 1; i < n; i++)
	{
		q = q->next;
	}
	p = q->next;
	change = real_change1(p->name);
	if (change == NULL)
		return 0;
	else
	{
		strcpy(p->name, change->name);
		strcpy(p->password,encryption (change->password));
		return 1;
	}
}
//人员的修改

int people_find(Node_p *head)
{
	char find[11];
	list_people_find();
	goto_xy(47, 10);

	strcpy(find,input_add_back());
	Node_p *p;
	for (p = head->next; (strcmp(p->name, find) != 0) && p->next != NULL; p = p->next)
	{
		continue;
	}
	if (strcmp(p->name, find) == 0)
	{
		char gd[17];
		strcpy(gd, p->password);
		u_encryption(gd);
		goto_xy(30, 16);
		printf("--------------------------------------------------------");
		goto_xy(37, 18);
		printf("用户名： %-10s        密码： %-16s", p->name, gd);
		goto_xy(50, 21);
		printf("是否需要修改？");
		goto_xy(36, 23);
		printf("[Enter]  确认              [Esc]  返回");
		goto_xy(0, 0);
		int flag_find;
		flag_find = choose_yn();
		if (flag_find == 1)
		{
			Node_p *change;
			change = real_change1(p->name);
			if (change == NULL)
				return 0;
			else
			{
				strcpy(p->name, change->name);
				strcpy(p->password, encryption(change->password));
				return 1;
			}
		}
		else
			return 0;

	}
	else
	{
		goto_xy(42, 17);
		printf("--------------------------------");
		goto_xy(52, 19);
		printf("查无此人！\a");
		goto_xy(52, 21);
		printf("3秒后返回");
		goto_xy(42, 23);
		printf("--------------------------------");
		goto_xy(0, 0);
		Sleep(3000);
		return 0;
	}

}
//人员查找


void yh_change(void)
{
	Node_p *head;

place_jump:head = open_people();
	if (head->next == NULL)
	{
		clrscr();
		kuangjia();
		goto_xy(50, 10);
		printf("人 员 信 息 管 理");
		goto_xy(41, 15);
		printf("没有任何人员信息，按 [+] 添加新的人员");
		goto_xy(50, 18);
		printf("按 [Esc] 返回菜单");

		int flag_empty_people;
		goto_xy(16, 28);
		printf("没有任何人员信息，按 [+] 添加新的场地                                      ");
		flag_empty_people = place_empty_choose();

		if (flag_empty_people == 0)//释放malloc
		{
			return;
		}
		else if (flag_empty_people == 1)
		{
			Node_p *add;
			char p[10] = "!$@#!$@#$";
			add = real_change1(p);
			if (add == NULL)
				return;
			people_add(head, add);
			goto place_jump;
		}
	}
	else
	{
		int flag_place;

		int n = 0;//表示链表中的节点个数
		Node_p *p;
		for (p = head->next; p != NULL; p = p->next)
		{
			n++;
		}
		int group_num;
		(n%7==0) ? (group_num = n / 7):(group_num = n / 7+1);
		n = 0;

		output_people(head->next, 1, group_num);
		int j = 0;
		Node_p *j_head;
		j_head = head->next;
		for (p = j_head; p != NULL; p = p->next)
		{
			j++;
		}
		j > 7 ? (j = 7) : (1);
		
		
		list_people_star(35, 11,11);
		flag_place = place_view_choose();
		int i = 11;
		while (1)
		{
			int max = 0;//最大不超过箭头范围
			if (flag_place == 3)//加
			{
				Node_p *add;//释放malloc
				char p[10] = "!$@#!$@#$";
				add = real_change1(p);
				if (add != NULL)
					people_add(head, add);
				goto place_jump;
			}
			else if (flag_place == 4)//删除
			{
				if (people_delete(head, ((i - 9) / 2) + (n * 7)))
					people_save(head);//释放malloc
				goto place_jump;
			}
			else if (flag_place == 5)//修改
			{
				if (people_change(head, ((i - 9) / 2) + (n * 7)))
					people_save(head);//释放malloc
				goto place_jump;
			}
			else if (flag_place == 8)//查找
			{
				if (people_find(head))
					people_save(head);//释放malloc
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
				for (p = j_head; p != NULL; p = p->next)
				{
					max++;
				}
			}
			else if (flag_place == 2)//箭头向下
			{	
				for (p = j_head; p != NULL; p = p->next)
				{
					max++;
				}
				(max > 7) ? (max = 7) : (1);
				if (i < 9 + 2 * max)
				{
					i += 2;
				}
			}
			else if (flag_place == 6)//箭头向左
			{
				i = 11;
				if (n > 0)
					n--;
				int l = 0;
				for (j_head = head->next; l < n; l++)
					j_head = j_head->next->next->next->next->next->next->next;
				output_people(j_head,n+1, group_num);
				for (p = j_head; p != NULL; p = p->next)
				{
					max++;
				}
			}
			else if (flag_place == 7)//箭头向右
			{
				i = 11;
				if (n+1 < group_num)
					n++;
				int l = 0;
				for (j_head = head->next; l < n; l++)
					j_head = j_head->next->next->next->next->next->next->next;
				output_people(j_head,n+1,group_num);
				for (p = j_head; p != NULL; p = p->next)
				{
					max++;
				}
			}
			list_people_star(35, i,(max>=7)?(max=25):(max=9+2*max));
			flag_place = place_view_choose();
		}
	}
}
//用户的信息

/////////////////////////////////////////////////////////////////////////////////////////////////
void gly_save(Node *gly)
{
	if (gly == NULL)
		return;
	FILE *topn;
	topn = fopen("topn.txt", "w");
	if (NULL == topn)
	{
		printf("\n\n\n\n\n\n\t\t\t管理员密码文件被破坏\a，请联系软件开发商，以获取技术支持，重置管理员密码！\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	rewind(topn);
	strcpy(gly->password, encryption(gly->password));
	fwrite(gly, sizeof(Node), 1, topn);
	save_time();
	fclose(topn);
	free(gly);
	return;
}
//管理员修改存储信息

void gly_change(void)
{

	Node *gly;
	gly = out_n();
	char p[10] = "!$@#!$@#$";
	int flag_gly_choose = list_gly_change_choose(gly);
	switch (flag_gly_choose)
	{
	case 1:Sleep(200); gly_save(real_change(p)); break;
	case 0:Sleep(200); return;
	}
}
//选择管理员后的操作

Node *real_change(char *cf)
{
	int flag_name_again;
	int flag_pass_long;
	char name[12];
	char pass1[18], pass2[18];

gbko:list_reg_in();

gbkd:goto_xy(47, 12);
	strcpy(name, input_add_back());
	if (strcmp(name, "!#%&(") == 0)
		return NULL;
	goto_xy(10, 28);
	printf("                                                  ");
	while (name[0] == '\0')
	{
		goto_xy(47, 12);
		printf("\a账号为空！");
		goto_xy(10, 28);
		printf("警告：账号为空，请重新输入！                       ");
		Sleep(2000);
		goto_xy(47, 12);
		printf("             ");
		goto gbkd;
	}

	flag_name_again = chongfu(name);
	while (flag_name_again == 0 && strcmp(name,cf)!=0)
	{
		goto_xy(47, 12);
		printf("\a账号重复！ ");
		goto_xy(10, 28);
		printf("警告：账号重复，请重新输入！                    ");
		Sleep(2000);
		goto_xy(47, 12);
		printf("             ");
		goto gbkd;
	}
	////////////////////////////////////////////////////////////用户名输入完成
gbk:goto_xy(47, 16);
	strcpy(pass1, input_pass_back());
	if (strcmp(pass1, "!#%&(") == 0)
		return NULL;
	flag_pass_long = pass_long(pass1);
	while (flag_pass_long == 0)
	{
		goto_xy(47, 16);
		printf("\a密码长度错误！  ");
		goto_xy(10, 28);
		printf("警告：密码长度错误，请输入8-16位！                  ");
		Sleep(2000);
		goto_xy(47, 16);
		printf("             ");


		goto_xy(47, 16);
		strcpy(pass1, input_pass_back());
		if (strcmp(pass1, "!#%&(") == 0)
			return NULL;
		flag_pass_long = pass_long(pass1);
		goto_xy(10, 28);
		printf("                                                  ");
		goto_xy(0, 0);
	}

	goto_xy(47, 20);
	strcpy(pass2, input_pass_back());
	if (strcmp(pass2, "!#%&(") == 0)
		return NULL;

	while (strcmp(pass1, pass2) != 0)
	{
		goto_xy(10, 28);
		printf("\a警告：两次密码输入不同！请3秒后重新输入！");
		Sleep(3000);
		goto_xy(47, 16);
		printf("                  ");
		goto_xy(47, 20);
		printf("                  ");
		goto gbk;

	}
	///////////////////////////////////////////////////////////////////密码输入完成
	goto_xy(10, 28);
	printf("按 [*] 可以切换密码显示模式。");

	int l = strlen(pass1);
	char out[19];
	int i;
	for (i = 0; i < l; i++)
	{
		out[i] = '*';
	}
	out[l] = '\0';
	///////////////////////////////////////////////////////////////////暗码

	list_reg_end();
	goto_xy(48, 12);
	printf("%s", name);
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
				printf("%s", pass1);
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
			break;
		else if (flag_choose_ayn == 0)
			goto gbko;
		flag_choose_ayn = choose_ayn();
		goto_xy(10, 28);
		printf("                                                  ");
		goto_xy(0, 0);
	}
	///////////////////////////////////////////////////////确认输入无误
	Node *ready_save;
	ready_save = (Node*)malloc(sizeof(Node));
	strcpy(ready_save->name, name);
	strcpy(ready_save->password, pass1);

	return ready_save; 
}
//管理员人员修改信息获取

Node_p *real_change1(char *cf)
{
	int flag_name_again;
	int flag_pass_long;
	char name[12];
	char pass1[18], pass2[18];

gbko:list_reg_in();

gbkd:goto_xy(47, 12);
	strcpy(name, input_add_back());
	if (strcmp(name, "!#%&(") == 0)
		return NULL;
	goto_xy(10, 28);
	printf("                                                  ");
	while (name[0] == '\0')
	{
		goto_xy(47, 12);
		printf("\a账号为空！");
		goto_xy(10, 28);
		printf("警告：账号为空，请重新输入！                       ");
		Sleep(2000);
		goto_xy(47, 12);
		printf("             ");
		goto gbkd;
	}

	flag_name_again = chongfu(name);	
	while (flag_name_again == 0 && strcmp(name, cf) != 0)
	{
		goto_xy(47, 12);
		printf("\a账号重复！ ");
		goto_xy(10, 28);
		printf("警告：账号重复，请重新输入！                    ");
		Sleep(2000);
		goto_xy(47, 12);
		printf("             ");
		goto gbkd;
	}
	////////////////////////////////////////////////////////////用户名输入完成
gbk:goto_xy(47, 16);
	strcpy(pass1, input_pass_back());
	if (strcmp(pass1, "!#%&(") == 0)
		return NULL;
	flag_pass_long = pass_long(pass1);
	while (flag_pass_long == 0)
	{
		goto_xy(47, 16);
		printf("\a密码长度错误！  ");
		goto_xy(10, 28);
		printf("警告：密码长度错误，请输入8-16位！                  ");
		Sleep(2000);
		goto_xy(47, 16);
		printf("             ");


		goto_xy(47, 16);
		strcpy(pass1, input_pass_back());
		if (strcmp(pass1, "!#%&(") == 0)
			return NULL;
		flag_pass_long = pass_long(pass1);
		goto_xy(10, 28);
		printf("                                                  ");
		goto_xy(0, 0);
	}

	goto_xy(47, 20);
	strcpy(pass2, input_pass_back());
	if (strcmp(pass2, "!#%&(") == 0)
		return NULL;

	while (strcmp(pass1, pass2) != 0)
	{
		goto_xy(10, 28);
		printf("\a警告：两次密码输入不同！请3秒后重新输入！");
		Sleep(3000);
		goto_xy(47, 16);
		printf("                  ");
		goto_xy(47, 20);
		printf("                  ");
		goto gbk;

	}
	///////////////////////////////////////////////////////////////////密码输入完成
	goto_xy(10, 28);
	printf("按 [*] 可以切换密码显示模式。");

	int l = strlen(pass1);
	char out[19];
	int i;
	for (i = 0; i < l; i++)
	{
		out[i] = '*';
	}
	out[l] = '\0';
	///////////////////////////////////////////////////////////////////暗码

	list_reg_end();
	goto_xy(48, 12);
	printf("%s", name);
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
				printf("%s", pass1);
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
			break;
		else if (flag_choose_ayn == 0)
			goto gbko;
		flag_choose_ayn = choose_ayn();
		goto_xy(10, 28);
		printf("                                                  ");
		goto_xy(0, 0);
	}
	///////////////////////////////////////////////////////确认输入无误
	Node_p *ready_save;
	ready_save = (Node_p*)malloc(sizeof(Node_p));
	strcpy(ready_save->name, name);
	strcpy(ready_save->password, pass1);

	return ready_save;
}
//用户添加