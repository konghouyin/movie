

//添加各种头文件，方便在各个.c 中使用
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include<string.h>

typedef struct np {
	char name[11];
	char password[17];
}Node;


typedef struct dnp {
	char name[11];
	char password[17];
	struct dnp *next;
}Node_p;

typedef struct di {
	int num;
	int site;
	int hang;
	int lie;
	struct di *next;
}place;



typedef struct yi {
	char name[35];
	int time_long;
	int money;
	int place_num;
	char style[5];
	struct yi *next;

}movie;



void clrscr(void);