#include <stdio.h>
/* strcmp */
#include <string.h>
/* getch */
#include <conio.h>
/* system */
#include <windows.h>
/* exit , rand */
#include <stdlib.h>
/* time */
#include <time.h>

#define CLIENT_SIZE 50 // 고객의 최대 수
#define False -1 // 반환값

/* 고객 구조체 선언 */
typedef struct {
    char name[15]; // 이름
    char rrn[15]; // 주민등록번호
    int account; // 계좌번호
    int money;   // 계좌에 들어있는 돈
    char id[10]; // 아이디
    char pw[10]; // 패스워드
} client;

/* 저장을 위한 구조체 선언 */
typedef struct { 
    char name_b[15]; 
    char rrn_b[15]; 
    int account_b; 
    int money_b;
    char id_b[10]; 
    char pw_b[10]; 
} client_b;

/* 화면출력 및 메뉴선택 함수 */
void menu() {
    printf("###############################################\n");
    printf("##                                           ##\n");
    printf("##                 ysu_bank                  ##\n");
    printf("##                                           ##\n");
    printf("##                                           ##\n");
    printf("##         1.로그인 2.회원가입 3.종료        ##\n");
    printf("##                                           ##\n");
    printf("###############################################\n");
}

/* 구조체 멤버에 정보 입력 (회원가입) 함수 */
int signup(client_b *infor_b) { 

    /* 인덱스 증가를 위해 정적변수 선언 
    정적변수는 프로그램이 시작될 때 초기화가 되고
    함수가 재호출 돼도 변수를 초기화 하지 않고 무시한다.*/
    static int count = 0; 

    printf("이름: ");
    scanf("%s", infor_b[count].name_b);

    printf("주민등록번호(특수문자제외): ");
    scanf("%s", infor_b[count].rrn_b);

    printf("아이디(최대9글자): ");
    scanf("%s", infor_b[count].id_b);

    printf("비밀번호(최대9글자): ");
    scanf("%s", infor_b[count].pw_b);

    /* 다음 불러오는 함수는 인덱스가 증가되어 다른 회원정보로 입력가능 
    count변수의 값은 즉 고객의 수와 같다. */
    count++; 

    return count;
}

/* 계좌번호 생성 */
void create_account(client *infor, client_b *infor_b, int index) {

    srand(time(NULL));
    infor_b[index].account_b = rand();
    infor[index].account = infor_b[index].account_b;
    
    infor[index].money = 0;
    infor_b[index].money_b = 0;
}

/* 로그인 및 로그인 확인 함수 */
int login(client *infor, client_b *infor_b, int count) {

    printf("-----------로그인-----------\n");
    printf("아이디: ");
    scanf("%s", infor->id);
    printf("비밀번호: ");
    scanf("%s", infor->pw);

    /* 방금 입력한 아이디와 회원가입 때 입력한 아이디를 반복해서 비교 */
    for(int i=0; i<count; i++){
        if(strcmp(infor->id, infor_b[i].id_b) == 0 && strcmp(infor->pw, infor_b[i].pw_b) == 0 ) {
            printf("\n\n사용자 확인 완료.");
            Sleep(2500);
            return i;
        }
        else if(i + 1 == count) { 
            printf("\n\n아이디 혹은 비밀번호가 다릅니다.");
            Sleep(2500);
            return False;
        }
    }
}

/* 은행메뉴 출력 함수 */
void menu_bank() {
    printf("################################################################\n");
    printf("##                                                            ##\n");
    printf("##                       ysu_bank                             ##\n");
    printf("##                                                            ##\n");
    printf("##                                                            ##\n");
    printf("## 1.입금 2.출금 3.계좌조회 4.계좌이체 5.로그인창 6.계좌생성  ##\n");
    printf("##                     7.종료                                 ##\n");
    printf("##                                                            ##\n");
    printf("################################################################\n");
}

/* 입금함수 */
void deposit(client_b *infor_b, int index) {
    
    int money;
    printf("%s님 입금 금액: ", infor_b[index].name_b);
    scanf("%d", &money);

    infor_b[index].money_b = money;
    printf("%s님의 남은 금액은 %d원입니다.",infor_b[index].name_b, infor_b[index].money_b);
    Sleep(2500);
}

/* 출금함수 */
void withdraw(client_b *infor_b, int index) {
    
    int money;
    printf("출금 금액: ");
    scanf("%d", &money);

    if(money > infor_b[index].money_b) {
        printf("출금 금액히 현재 잔고보다 많습니다.");
    }
    else{
        infor_b[index].money_b -= money;
        printf("%s님의 남은 금액은 %d원입니다.",infor_b[index].name_b, infor_b[index].money_b);
    }
    Sleep(2500);
}

/* 계좌조회함수 */
void track_account(client_b *infor_b, int index) {

    printf("%s님의 계좌번호: %d\n", infor_b[index].name_b, infor_b[index].account_b);
    printf("%s님의 현재 금액: %d원\n", infor_b[index].name_b, infor_b[index].money_b);
    Sleep(2500);
}

/* 계좌번호 입력시 해당하는 사람의 인덱스 값을 찾아주는 함수 */
int find_account(client_b *infor_b, int account, int count) {

    for(int i=0; i<count; i++) {
        if(infor_b[i].account_b == account) {
            return i;
        }
        else if(i + 1 == count) {
            printf("해당하는 계좌가 없습니다.");
            return False;
        }
    }
}

/* 계좌이체 함수 */
void remittance(client_b *infor_b, int index_a, int count) {
    
    int account, index, money;

        printf("이체할 계좌번호 입력: ");
        scanf("%d", &account);

        index = find_account(infor_b, account, count);
        if(index >= 0) {
            printf("이체할 금액 입력: ");
            scanf("%d", &money);

            infor_b[index_a].money_b -= money;
            infor_b[index].money_b += money;

            printf("이체 완료!");
            Sleep(2500);
        }
        else {
            Sleep(1500);
        }
}

/* 함수관리 */
void main_system() {

    client infor[CLIENT_SIZE];
    client_b infor_b[CLIENT_SIZE];
    int input_num = 0, count, index;
    while(1) {
        while(1) {

            system("cls");
            menu();
            input_num = _getch() -'0';

            if(input_num == 1) {
                system("cls");
                index = login(infor, infor_b, count);
                if(index >= 0) {
                    break;
                }
                else {
                    continue;
                }
            }
            else if(input_num == 2) {
                system("cls");
                count = signup(infor_b);
            }
            else if(input_num == 3) {
                exit(0);
            }
            else {
                printf("잘못된 번호입니다.");
                Sleep(1000);
            }
        }

        while(1) {

            system("cls");
            menu_bank();
            input_num = _getch() - '0';

            if(input_num == 1) {
                system("cls");
                deposit(infor_b, index);
                continue;
            }
            else if(input_num == 2) {
                system("cls");
                withdraw(infor_b, index);
                continue;
            }
            else if(input_num == 3) {
                system("cls");
                track_account(infor_b, index);
                continue;
            }
            else if(input_num == 4) {
                system("cls");
                remittance(infor_b, index, count);
                continue;
            }
            else if(input_num == 5) {
                break;
            }
            else if(input_num == 6) {
                system("cls");
                create_account(infor, infor_b, index);
                printf("계좌생성완료");
                Sleep(2000);
            }
            else if(input_num == 7) {
                exit(0);
            }
            else {
                printf("잘못된 번호입니다.");
                Sleep(1000);
            }
        }
    }
}

int main() {

    main_system();
    _getch();
}