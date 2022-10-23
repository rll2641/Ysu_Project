#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

// 회원가입시 최대 글자 수
#define limit 8
// 시간 선택
#define hour 1
#define thour 2

// 메뉴 창
void print_menu();
// 메뉴 함수
void menu();
// 회원가입 함수
char *signup_id();
char *signup_pw();
// 로그인 함수
char *login_id();
char *login_pw();
// 시간 선택 함수
int select_time();
// 남은시간 확인 함수
void check_time();

int main(){

    menu();
    return 0;
}

void print_menu(){

    printf("##################################################\n");
    printf("##                                              ##\n");
    printf("##           (로그인 전 회원가입 필수!)         ##\n");
    printf("##          1.로그인 2.회원가입 3.pc종료        ##\n");
    printf("##                                              ##\n");
    printf("##                                              ##\n");
    printf("##       영산대학교 10191541/ai컴공/조지훈      ##\n");
    printf("##################################################\n");

}

void menu(){

    char *id, *pw, *id2, *pw2;
    int select_num = 0;

    while(1){

        print_menu();
        select_num = _getch()- '0';

        while(1){
            if (select_num == 1){
                system("cls");
                id2 = login_id();
                pw2 = login_pw();
                if(memcmp(id, id2, limit) == 0 && memcmp(pw, pw2, limit) == 0){
                    printf("로그인 중\n");
                    Sleep(2000);
                    printf("회원정보가 일치합니다.\n");
                    Sleep(2000);
                    free(id);free(id2);free(pw);free(pw2);
                    system("cls");
                    check_time();
                }
                else{
                    system("cls");
                    printf("아이디 비밀번호를 다시 확인해주세요.\n");
                    break;
                }
            }
            else if (select_num == 2){
                system("cls");
                id = signup_id();
                pw = signup_pw();
                break;
            }
            else if (select_num == 3){
                exit(0);
            }
        }
    }
}

char *signup_id(){

    char *id = (char*)malloc(limit + 1);

    printf("아이디,비밀번호는 영어 소문자,숫자의 조합으로 최대 8글자까지 가능합니다.\n");
    printf("아이디 입력: ");
    gets(id);
    printf("당신의 아이디 확인: %s\n", id);
    Sleep(1500);

    return id;
}

char *signup_pw(){

    char *pw = (char*)malloc(limit + 1);

    printf("비밀번호 입력: ");
    gets(pw);
    printf("당신의 비밀번호 확인: %s\n", pw);
    Sleep(1500);
    printf("회원가입완료!\n");
    Sleep(1500);
    system("cls");

    return pw;
}

char *login_id(){

    char *id = (char*)malloc(limit + 1);

    printf("아이디: ");
    gets(id);

    return id;
}

char *login_pw(){

    char *pw = (char*)malloc(limit + 1);

    printf("비밀번호:");
    gets(pw);

    return pw;
}

int select_time(){

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    int num;

    printf("원하시는 시간을 선택 해주세요.\n");
    printf("해당 시간이 지나면 자동적으로 컴퓨터가 종료하게 됩니다.\n");
    printf("[1. 1시간 / 2. 2시간]\n");

    num = _getch() - '0';

    if (num == 1){
        system("cls");
        printf("1시간 선택완료\n");
        printf("지금부터 1시간뒤에 자동적으로 컴퓨터가 꺼지게 됩니다.\n");
        printf("현재 시간: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("종료 시간: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour+1, tm.tm_min, tm.tm_sec);
        Sleep(5000);
        system("cls");
        return hour;
    }
    else if (num == 2){
        system("cls");
        printf("2시간 선택완료\n");
        printf("지금부터 2시간뒤에 자동적으로 컴퓨터가 꺼지게 됩니다.\n");
        printf("현재 시간: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("종료 시간: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour+2, tm.tm_min, tm.tm_sec);
        Sleep(5000);
        system("cls");
        return thour;
    }
}

void check_time(){

    int check, t = 0;

    check = select_time();

    if(check == hour){
        t = 3600;
        while(t>0){
            printf("남은시간: %d:%d:%d\n", t/3600, (t%3600)/60, (t%3600)%60);
            t--;
            Sleep(1000);
            system("cls");
        }
        system("shutdown -s -t 1");
    }
    else if(check == thour){
        t = 7200;
        while(t>0){
            printf("남은시간: %d:%d:%d\n", t/3600, (t%3600)/60, (t%3600)%60);
            t--;
            Sleep(1000);
            system("cls");
        }
        system("shutdown -s -t 1");
    }
}