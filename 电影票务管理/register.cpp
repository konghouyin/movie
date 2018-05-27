#include"include.h"



void kuangjia(void);//框架
char* encryption(char*);//加密函数
char* u_encryption(char* p);//解密函数
void goto_xy(int x, int y);//光标跳转

int list_reg_choose(void);//告知用户相关条规，并确认
void reg_really(void);//开始注册
void list_reg_in(void);//开始注册  打印相关输入列表
char* input_add_back(void);//字符串的获取
char* input_pass_back(void);//密码的获取
void list_reg_end(void);//输入结束并确认
int choose_ayn(void);//获取 是或否或星号
void list_reg_pass(void);//打印输入管理员密码的通知
void save_time(void);//储存缓冲
void right(void);//注册成功
void wrong(void);//注册失败


void reg(void)
{
	int flag_reg_choose;
	flag_reg_choose =list_reg_choose();
	switch (flag_reg_choose)
	{
	case 0: return;
	case 1:Sleep(200); reg_really();
	}
	return;
}
//注册信息

int chongfu(char *name)
{
	Node *top;
	top = (Node*)malloc(sizeof(Node));

	FILE *topn;
	topn = fopen("topn.txt", "r");
	if (NULL == topn)
	{
		printf("\n\n\n\n\n\n\t\t\t管理员文件被破坏\a，请联系软件开发商，以获取技术支持！\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	getc(topn);
	if (feof(topn))
	{
		printf("\n\n\n\n\n\n\t\t\t管理员文件被破坏\a，请联系软件开发商，以获取技术支持！\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	rewind(topn);
	fread(top, sizeof(Node), 1, topn);
	if ((strcmp(top->name, name)) == 0)
	{
		free(top);
		return 0;
	}
	

	FILE *midn;
	midn = fopen("midn.txt", "r");
	if (midn == NULL)
	{
		fprintf(stdout, "\n\t\t\t系统文件已损坏，请联系管理员！\a\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	getc(midn);
	if (feof(midn) != 0)
	{
		fclose(midn);
		return 1;
	}
	else
	{
		rewind(midn);
		Node_p *mid;
		mid = (Node_p*)malloc(sizeof(Node_p));
		while (fread(mid, sizeof(Node_p), 1, midn) != 0)
		{
			if ((strcmp(mid->name, name)) == 0)
			{
				free(mid);
				return 0;
			}
		}
		fclose(midn);
		free(mid);
		return 1;
	}
}
//用户名查重

int pass_long(char* pass)
{
	int l = strlen(pass);
	if (l <= 16 && l >= 8)
		return 1;
	else
		return 0;
}
//密码长度控制

Node* out_n(void)
{
	Node *top;
	top = (Node*)malloc(sizeof(Node));

	FILE *topn;
	topn = fopen("topn.txt", "r");
	if (NULL == topn)
	{
		printf("\n\n\n\n\n\n\t\t\t管理员密码文件被破坏\a，请联系软件开发商，以获取技术支持，重置管理员密码！\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	getc(topn);
	if (feof(topn))
	{
		printf("\n\n\n\n\n\n\t\t\t管理员密码文件被破坏\a，请联系软件开发商，以获取技术支持，重置管理员密码！\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	rewind(topn);
	fread(top, sizeof(Node), 1, topn);
	strcpy(top->password, u_encryption(top->password));
	fclose(topn);

	return top;
}
//管理员密码打开

void save(Node_p* mid)
{
	FILE *midn;
	midn = fopen("midn.txt", "a");
	if (midn == NULL)
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
		save_time();
		if (fwrite(mid, sizeof(Node_p), 1, midn) == 1)
		{
			fflush(midn);
			right();
			Sleep(3000);
			return;
		}
		else
		{
			wrong();
			Sleep(3000);
			return;
		}
	}
}
//注册信息存入


void reg_really(void)
{
	int flag_name_again;
	int flag_pass_long;
	char name[12];
	char pass1[18],pass2[18];
	
	gbko:list_reg_in();

	gbkd:goto_xy(47, 12);
	strcpy(name, input_add_back());
	if (strcmp(name, "!#%&(") == 0)
		return;
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
	while (flag_name_again == 0)
	{
		goto_xy(47, 12);
		printf("\a账号重复！ ");
		goto_xy(10,28);
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
		return;
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
			return;
		flag_pass_long = pass_long(pass1);
		goto_xy(10, 28);
		printf("                                                  ");
		goto_xy(0, 0);
	}

	goto_xy(47, 20);
	strcpy(pass2, input_pass_back());
	if (strcmp(pass2, "!#%&(") == 0)
		return;

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
	list_reg_pass();
	char gly_pass[19];
	Node *gly=out_n();//获取正确密码

	int t = 0;

	pask:goto_xy(47, 14);
	strcpy(gly_pass, input_pass_back());
	if (strcmp(gly_pass, "!#%&(") == 0)
		return;
	t++;
	while ((strcmp(gly_pass, gly->password)))
	{
		if (t > 4)
		{

			goto_xy(47, 14);
			printf("        Wrong!    ");
			goto_xy(43, 20);
			printf("错误次数过多，程序将于5秒后自动退出！");
			printf("\n\n\t\t\t\t如需重置管理员密码，请联系软件开发商，以获取技术支持！");
			goto_xy(10, 28);
			printf("警告：密码多次输入错误！                                          \a");
			Sleep(5000);
			exit(EXIT_FAILURE);
		}

		goto_xy(10, 28);
		printf("\a警告：密码错误！  请3秒后重新输入！                ");
		goto_xy(47, 14);
		printf("\a密码错误！        ");
		Sleep(3000);
		goto_xy(47, 14);
		printf("                    ");
		goto_xy(10, 28);
		printf("警告：密码错误！  请重新输入！ 你还有%d次机会                     ",5-t); 
		
		
		goto pask;
	}
	//////////////////////////////////////////////////////管理员密码无误
	Node_p *mid;
	mid = (Node_p*)malloc(sizeof(Node_p));
	strcpy(mid->name, name);
	strcpy(mid->password, encryption(pass1));
	save(mid);

	free(mid);
	free(gly);

	return;
}
//正式进入注册