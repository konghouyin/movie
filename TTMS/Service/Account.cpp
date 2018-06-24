#include "Account.h"
#include "EntityKey.h"
#include "../Common/list.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern account_t gl_CurUser;//设置一个全局变量，存储当前登录的用户信息

//创建系统初始化账号admin
//查询管理员文件是否存在，如果不存在就新建一个
void Account_Srv_InitSys() {
	if (Account_Perst_CheckAccFile())
		return;
	printf("系统检测到初次使用,请初始化系统管理员的信息：\n");
	account_t data_admin;//创建一个人员数据域
	char type[] = "account";
	data_admin.id = EntKey_Srv_CompNewKey(type);//分配程序唯一对应主键
	printf("\t\t\t请输入管理员名称：");
	fgets(data_admin.username,29,stdin);//vs 2017不支持gets(),使用fgets()代替
	int l = strlen(data_admin.username);
	data_admin.username[l - 1] = '\0';
	printf("\t\t\t请输入管理员密码：");	
	fgets(data_admin.password, 29, stdin);
	l = strlen(data_admin.password);
	data_admin.password[l - 1] = '\0';
	data_admin.type = (account_type_t)9; //注册为管理员账号，作为软件初始化密码初始化
	if (Account_Srv_Add(&data_admin))//文件中直接存贮数据域，所以不需要导入链表
	{
		printf("成功初始化管理员!");
	}
	else
	{
		printf("初始化失败，请联系软件开发商，以获取技术支持！");
		exit(EXIT_FAILURE);
	}
}

//验证登录账号是否已存在，存在，保存登录用户信息到全局变量gl_CurUser，return 1；否则return 0
int Account_Srv_Verify(char usrName[], char pwd[]) {
	account_t usr;
	account_list_t head;
	List_Init(head, account_node_t);//创建链表

	Account_Srv_FetchAll(head);
	//提取所有用户账号信息，保存到list链表中，通过调用Account_Perst_SelectAll(list)函数实现
	/*需要将头指针作为参数传入持久化层进行信息读取*/
	
	Account_Perst_SelByName(usrName, &usr);
	//根据用户名载入账号,载入成功 return 1；否则 return 0
	//usr作为指针参数传入，可以更新usr为最新的数据域
	//该函数的主要目的是，跟新usr，以便于下面的密码查询
	//问题：文件已经存入链表，可以在链表中进行查询，不用再次读取文件，降低文件效率


	if (!Account_Srv_FindByUsrName(head, usrName))
	//验证用户名是否存在，遍历list，若存在，返回对应结点指针；否则，返回null
		return 0;
	if (strcmp(usr.password, pwd) == 0) {
		gl_CurUser = usr;
		return 1;
	}
	return 0;
}


//验证用户名是否存在，遍历list，若存在，返回对应结点指针；否则，返回null
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {
	account_node_t  *pos;
	List_ForEach(list, pos)//链表历遍函数
		if (strcmp(pos->data.username, usrName) == 0)
			return pos;
	return NULL;
}

//添加一个用户账号，通过调用Account_Perst_Insert(data)函数实现
int Account_Srv_Add(const account_t *data) {
	return Account_Perst_Insert(data);
}

//修改一个用户账号，通过调用Account_Perst_Update(data)函数实现
int Account_Srv_Modify(const account_t *data) {
	return Account_Perst_Update(data);
}

//删除一个用户账号，通过调用Account_Perst_DeleteByID(usrID)函数实现
int Account_Srv_DeleteByID(int usrID) {
	return Account_Perst_DeleteByID(usrID);
}

//提取usrID对应的用户账号信息，通过调用Account_Perst_SelectByID(usrID, buf)函数实现
int Account_Srv_FetchByID(int usrID, account_t *buf) {
	return Account_Perst_SelectByID(usrID, buf);
}

//提取usrName对应的用户账号信息，通过调用Account_Perst_SelByName(usrName, buf)函数实现
int Account_Srv_FetchByName(char usrName[], account_t *buf) {
	return Account_Perst_SelByName(usrName, buf);
}

//提取所有用户账号信息，保存到list链表中，通过调用Account_Perst_SelectAll(list)函数实现
int Account_Srv_FetchAll(account_list_t list) {
	return Account_Perst_SelectAll(list);
}


