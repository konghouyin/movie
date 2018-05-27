#include"include.h"




char* u_encryption(char* p);//解密函数

void list_log_in(void);//登录输入界面
void goto_xy(int x, int y);//光标跳转
Node* out_n(void);//管理员信息
int chongfu(char *name);//用户名查重
char* input_add_back(void);//用户名特殊登录
char* input_pass_back(void);//密码特殊获取

void gly_(void);//管理员函数



int pass_true(char *name,char *pass)
{
	FILE *midn;
	midn = fopen("midn.txt", "r");
	if (midn == NULL)
	{
		goto_xy(10, 28);
		fprintf(stdout, "系统文件已损坏，请联系管理员！");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	else
	{
		Node_p *mid;
		mid = (Node_p*)malloc(sizeof(Node_p));
		while (fread(mid, sizeof(Node_p), 1, midn) != 0)
		{
			if ((strcmp(mid->name, name)) == 0)
			{
				if (strcmp((u_encryption(mid->password)), pass) == 0)
				{
					fclose(midn);
					free(mid);
					return 1;
				}
			}
		}
		fclose(midn);
		return 0;
	}
}
//确认密码正确性

static int i = 0;

void log(void)
{
	
	list_log_in();
	char name[12];
	char pass[18];

lkj:if (i > 4)
	{

		goto_xy(47, 17);
		printf("        Wrong!    ");
		goto_xy(43, 21);
		printf("错误次数过多，程序将于5秒后自动退出！");
		printf("\n\n\t\t\t\t如需重置密码，请联系管理员或软件开发商，以获取技术支持！");
		goto_xy(10, 28);
		printf("警告：密码多次输入错误！                                          \a");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}

	goto_xy(47, 13);
	strcpy(name, input_add_back());
	if (strcmp(name, "!#%&(") == 0)
		return ;
	/////////////////////////////////////////////////////获取字符

	Node *gly = out_n();//获取管理员信息

	if (strcmp(name,gly->name)==0)
	{
		goto_xy(47, 17);
		strcpy(pass, input_pass_back());
		i++;
		if (strcmp(pass, "!#%&(") == 0)
			return;
///////////////////////////////////////////////////////////获取密码
		if (strcmp(pass, gly->password) == 0)
		{
			i = 0;
			gly_();
		}
		else
		{
			goto_xy(47, 17);
			printf("\a密码错误！      ");
			goto_xy(10, 28);
			printf("警告：密码错误，请3秒后重新输入！                               ");
			if (i == 5)
			{
				goto lkj;
			}
			Sleep(3000);
			goto_xy(10, 28);
			printf("警告：密码错误，请重新输入！      你还有%d次机会                ", 5 - i);
			goto_xy(47, 17);
			printf("                  ");
			goto_xy(47, 13);
			printf("                  ");
			goto lkj;
		}
	}
	else
	{
		int flag_name;
		flag_name = chongfu(name);
		while (flag_name == 1)
		{
			goto_xy(47, 13);
			printf("\a没有该用户！    ");
			goto_xy(10, 28);
			printf("警告：没有该用户，请重新输入！                       ");
			Sleep(2000);
			goto_xy(47, 13);
			printf("                  ");
			goto lkj;
		}
		/////////////////////////////////////////////////用户名已确认
		goto_xy(10, 28);
		printf("                                                                                ");
		goto_xy(47, 17);
		strcpy(pass, input_pass_back());
		i++;
		if (strcmp(pass, "!#%&(") == 0)
			return;
		///////////////////////////////////////////////////获取密码

		int flag_pass;
		flag_pass = pass_true(name, pass);
		while(flag_pass == 0)
		{
			goto_xy(47, 17);
			printf("\a密码错误！      ");
			goto_xy(10, 28);
			printf("警告：密码错误，请3秒后重新输入！                                ");
			if (i == 5)
			{
				goto lkj;
			}
			Sleep(3000);
			goto_xy(10, 28);
			printf("警告：密码错误，请重新输入！      你还有%d次机会                ", 5 - i);
			goto_xy(47, 17);
			printf("                  ");
			goto_xy(47, 13);
			printf("                  ");
			goto lkj;
		}

		//////////////////////////////////////////////////密码正确
		i = 0;
		printf("ok");//////////////////////////////////////////////////////替换函数

	}

	return ;
}
//登录函数