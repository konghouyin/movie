
#include "Ticket_UI.h"
#include "../Service/EntityKey.h"
#include "../Common/list.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Persistence/Ticket_Persist.h"
#include "../Persistence/Play_Persist.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Service/Seat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char * Status(int i)
{
	static char back[5];
	if (i == 1)
	{
		strcpy(back, "√");
		return back;
	}
	else if (i == 0)
	{
		strcpy(back, "□");
		return back;
	}
	else if (i == 9)
	{
		strcpy(back, "◎");
		return back;
	}
	else
	{
		strcpy(back, "");
		return back;
	}
}

void Ticket_UI_show(int schID)
{
	int rowmax = 0, colmax = 0;
	static char listout[15][15][5];
	int value = 0;
	seat_t buf;
	ticket_list_t list, s;
	List_Init(list, ticket_node_t);

	Ticket_Srv_FetchBySchID(list, schID);

	List_ForEach(list, s)
	{
		strcpy(listout[Seat_Srv_FetchByID(s->data.seat_id, &buf),buf.row][Seat_Srv_FetchByID(s->data.seat_id, &buf), buf.column], Status(s->data.status));
		if (buf.row > rowmax)
			rowmax = buf.row;
		if (buf.column > colmax)
			colmax = buf.row;
	}

	int i;
	printf("\t\t\t\t\t%4c ", ' ');
	for (i = 1; i <= rowmax; i++) {
		printf("%4d", i);
	}
	printf("\n\t\t\t\t------------------------------------------------------------------\n");
	//显示数据
	i = 1;
	int j = 1;
	for (; i <= colmax; i++ )
	{
		j = 1;
		printf("\t\t\t\t\t%2d行: ", i);
		for (; j <= rowmax; j++)
		{
			printf("%4s", listout[i][j]);
		}
		printf("\n\n");
	}


}
//通过演出计划ID 打印购票表格


