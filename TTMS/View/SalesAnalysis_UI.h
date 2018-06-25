#pragma once


#ifndef SALESANALYSIS_UI_H_
#define SALESANALYSIS_UI_H_
#include "../Common/list.h"
#include "../Service/Account.h"
#include "../Service/Play.h"
#include "../Service/Sale.h"
#include "../Service/SalesAnalysis.h"


void SalesAanalysis_UI_BoxOffice();

void SalesAanalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate);

void SalesAanalysis_UI_MgtEntry();
void SalesAnalysis_UI_StatSale_all(int usrID, user_date_t stDate, user_date_t endDate);

#endif /* SALESANALYSIS_UI_H_ */


