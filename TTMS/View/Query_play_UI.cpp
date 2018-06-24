#include "Query_Play_UI.h"
#include "../Service/Play.h"
#include "../Persistence/Query_Persist.h"
#include "../Service/Schedule.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Service/Studio.h"
#include "../Persistence/Ticket_Persist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"
void DisplayQueryPlay(void)
{
	while (_kbhit()){getch();}
	char fileName[30];
	play_t play;

	char choice;
	do {
		while (_kbhit()){getch();}
		memset(fileName, 0, sizeof(fileName));
		printf("\t\t\tPlease input the play name:");
		scanf("%s", fileName);
		printf("\n\t\t\t=======================================================\n");
		printf("\n\t\t\t****************  Play Information List  ***************\n");
		if (Query_PlayName(fileName, &play)) {
			printf("\t\t\tID\t\tName\t\tArea\t Rating\t\tStart date\t End date\tPrice\n");
			printf("\t\t\t-------------------------------------------------------\n");
			printf("\t\t\t%d\t\t%s\t\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%d\n", play.id,
				play.name, play.area,
				(play.rating == 1 ? "child   " : (play.rating == 2 ? "teenager" : "adult   ")),
				play.start_date.year, play.start_date.month,
				play.start_date.day, play.end_date.year,
				play.end_date.month, play.end_date.day, play.price);
			schedule_t  sched;
			studio_t studio = { 0 };
			//		seat_list_t list, int studio_id
			if (Query_Schedule_By_PlayId(play.id, &sched)) {
				Query_Studio_By_Schedule(sched.studio_id, &studio);
				printf("\t\t\tthe play will be show at %d:%d:%d %d:%d on %s studio\n", sched.date.year, sched.date.month,
					sched.date.day, sched.time.hour,
					sched.time.minute, studio.name);
				printf("\t\t\thave the seat %d , have sold %d, have %d is selling\n", Seat_Number_Count(sched.studio_id), Sold_Ticket_Count(sched.id),
					Seat_Number_Count(sched.studio_id) - Sold_Ticket_Count(sched.id));
			}
			else {
				printf("\t\t\tsorry, the play is not show!\n");
			}
			printf("\t\t\t[R]eturn, [B]ooking, [A]gain:");
			while (_kbhit()){getch();}
			scanf("%c", &choice);
			switch (choice) {
			case 'a':
			case 'A':
				break;
			case 'B':
			case 'b':
				//Sale the ticket
				break;
			}
		}
		else {
			printf("\t\t\tthe play name is not exit!\n");
			printf("\t\t\t[R]eturn, [B]ooking, [A]gain:");
			while (_kbhit()){getch();}
			scanf("%c", &choice);
			switch (choice) {
			case 'a':
			case 'A':
				break;
			case 'B':
			case 'b':
				//Sale the ticke
				break;
			}
		}
	} while (choice != 'r' && choice != 'R');
}


