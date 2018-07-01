#pragma once


#ifndef STUDIO_UI_H_
#define STUDIO_UI_H_
#include "Account_UI.h"
#include "../Service/Account.h"

int Studio_UI_Add(void);

int Studio_UI_Modify(int id);

int Studio_UI_Delete(int id);

void Studio_UI_MgtEntry(account_type_t type);
int Studio_UI_MgtEntry_schedule(void);

#endif /* STUDIO_UI_H_ */
