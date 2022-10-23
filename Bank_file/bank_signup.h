#pragma once

#pragma warning(disable:4996)
#pragma warning(disable:4267)

#include "bank_menu.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

/* 최대 고객 수 */
#define Max_Client 50
/* 배열 크기 */
#define Length 15
/* 파일 이름 */
#define File_Name "data.bin"
/* 반환 값 */
#define True 1
#define False 0

typedef struct Client {
    char name[Length];
    char phone[Length];
    char id[Length];
    char pw[Length];
    int account;
    int money;
} Client;

int examine_overlap(Client*, FILE*);
void create_account(Client*);
void signup(Client*, FILE*);
int login(FILE*);