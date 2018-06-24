#pragma once


#ifndef 	SALETICKET_UI_H_
#define 	SALETICKET_UI_H_

#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Seat.h"
#include "../Service/Account.h"
#include "../Service/Ticket.h"
/*
void 	DisplayTicketMenu(account_t *acco_p);
void 	GetRowAndColBy_SeatId (int seat_id , int * row , int *col) ;
void 	DisplayStudioSeatInfoBy_Schedule (int 	**seat_info , int row , int col) ;
void 	DisplayTicketMenu(account_t *acco_p) ;
void 	ReturnBackTicketMenu ()  ;*/
void Print_Play(play_list_t list);

void Ticket_Info(ticket_t *data,int id);

char * Status(int i);

//根据剧目ID显示演出计划
void Sale_UI_ShowScheduler(int playID);

//根据计划ID，显示演出票
void Sale_UI_ShowTicket(int schID);

int Sale_UI_SellTicket(int ticket_id);


void Sale_UI_MgtEntry();

//退票
void Sale_UI_ReturnTicket(int ticket_id);

#endif
