#pragma once
#include "bank_menu.h"
#include "bank_signup.h"

void deposit(FILE*, int);
void withdraw(FILE*, int);
void track_account(FILE*, int);
int find_account(FILE*, int);
void remittance(FILE*, int);