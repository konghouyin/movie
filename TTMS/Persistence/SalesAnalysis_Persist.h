#pragma once


#ifndef SALESANALYSISPERSIST_H_
#define SALESANALYSISPERSIST_H_
#include "../Service/SalesAnalysis.h"
#include "../Service/Play.h"
#include "../Service/Sale.h"

int Salesanalysis_Perst_Insert(const salesanalysis_t *data);
int SalesAnalysis_Perst_SelectAll(salesanalysis_list_t list);
int Sale_Perst_SelectAll(sale_list_t list);

#endif /* SALESANALYSISPERSIST_H_ */
