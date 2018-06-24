
#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_

#include "../Common/list.h"
#include "../Service/Account.h"

static const int ACCOUNT_PAGE_SIZE = 5;

char *usr_type(int i);
int SysLogin();
int GetPassword(char password[]);
void Account_UI_MgtEntry();
int Account_UI_Add(account_list_t list);
int Account_UI_Modify(account_list_t list, char usrName[]);
int Account_UI_Delete(account_list_t list, char usrName[]);
int Account_UI_Query(account_list_t list, char usrName[]);
int Account_UI_Modify_other(account_list_t list, char usrName[]);


#endif /* ACCOUNT_UI_H_ */

