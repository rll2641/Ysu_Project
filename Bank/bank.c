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

#define CLIENT_SIZE 50 // ���� �ִ� ��
#define False -1 // ��ȯ��

/* �� ����ü ���� */
typedef struct {
    char name[15]; // �̸�
    char rrn[15]; // �ֹε�Ϲ�ȣ
    int account; // ���¹�ȣ
    int money;   // ���¿� ����ִ� ��
    char id[10]; // ���̵�
    char pw[10]; // �н�����
} client;

/* ������ ���� ����ü ���� */
typedef struct { 
    char name_b[15]; 
    char rrn_b[15]; 
    int account_b; 
    int money_b;
    char id_b[10]; 
    char pw_b[10]; 
} client_b;

/* ȭ����� �� �޴����� �Լ� */
void menu() {
    printf("###############################################\n");
    printf("##                                           ##\n");
    printf("##                 ysu_bank                  ##\n");
    printf("##                                           ##\n");
    printf("##                                           ##\n");
    printf("##         1.�α��� 2.ȸ������ 3.����        ##\n");
    printf("##                                           ##\n");
    printf("###############################################\n");
}

/* ����ü ����� ���� �Է� (ȸ������) �Լ� */
int signup(client_b *infor_b) { 

    /* �ε��� ������ ���� �������� ���� 
    ���������� ���α׷��� ���۵� �� �ʱ�ȭ�� �ǰ�
    �Լ��� ��ȣ�� �ŵ� ������ �ʱ�ȭ ���� �ʰ� �����Ѵ�.*/
    static int count = 0; 

    printf("�̸�: ");
    scanf("%s", infor_b[count].name_b);

    printf("�ֹε�Ϲ�ȣ(Ư����������): ");
    scanf("%s", infor_b[count].rrn_b);

    printf("���̵�(�ִ�9����): ");
    scanf("%s", infor_b[count].id_b);

    printf("��й�ȣ(�ִ�9����): ");
    scanf("%s", infor_b[count].pw_b);

    /* ���� �ҷ����� �Լ��� �ε����� �����Ǿ� �ٸ� ȸ�������� �Է°��� 
    count������ ���� �� ���� ���� ����. */
    count++; 

    return count;
}

/* ���¹�ȣ ���� */
void create_account(client *infor, client_b *infor_b, int index) {

    srand(time(NULL));
    infor_b[index].account_b = rand();
    infor[index].account = infor_b[index].account_b;
    
    infor[index].money = 0;
    infor_b[index].money_b = 0;
}

/* �α��� �� �α��� Ȯ�� �Լ� */
int login(client *infor, client_b *infor_b, int count) {

    printf("-----------�α���-----------\n");
    printf("���̵�: ");
    scanf("%s", infor->id);
    printf("��й�ȣ: ");
    scanf("%s", infor->pw);

    /* ��� �Է��� ���̵�� ȸ������ �� �Է��� ���̵� �ݺ��ؼ� �� */
    for(int i=0; i<count; i++){
        if(strcmp(infor->id, infor_b[i].id_b) == 0 && strcmp(infor->pw, infor_b[i].pw_b) == 0 ) {
            printf("\n\n����� Ȯ�� �Ϸ�.");
            Sleep(2500);
            return i;
        }
        else if(i + 1 == count) { 
            printf("\n\n���̵� Ȥ�� ��й�ȣ�� �ٸ��ϴ�.");
            Sleep(2500);
            return False;
        }
    }
}

/* ����޴� ��� �Լ� */
void menu_bank() {
    printf("################################################################\n");
    printf("##                                                            ##\n");
    printf("##                       ysu_bank                             ##\n");
    printf("##                                                            ##\n");
    printf("##                                                            ##\n");
    printf("## 1.�Ա� 2.��� 3.������ȸ 4.������ü 5.�α���â 6.���»���  ##\n");
    printf("##                     7.����                                 ##\n");
    printf("##                                                            ##\n");
    printf("################################################################\n");
}

/* �Ա��Լ� */
void deposit(client_b *infor_b, int index) {
    
    int money;
    printf("%s�� �Ա� �ݾ�: ", infor_b[index].name_b);
    scanf("%d", &money);

    infor_b[index].money_b = money;
    printf("%s���� ���� �ݾ��� %d���Դϴ�.",infor_b[index].name_b, infor_b[index].money_b);
    Sleep(2500);
}

/* ����Լ� */
void withdraw(client_b *infor_b, int index) {
    
    int money;
    printf("��� �ݾ�: ");
    scanf("%d", &money);

    if(money > infor_b[index].money_b) {
        printf("��� �ݾ��� ���� �ܰ��� �����ϴ�.");
    }
    else{
        infor_b[index].money_b -= money;
        printf("%s���� ���� �ݾ��� %d���Դϴ�.",infor_b[index].name_b, infor_b[index].money_b);
    }
    Sleep(2500);
}

/* ������ȸ�Լ� */
void track_account(client_b *infor_b, int index) {

    printf("%s���� ���¹�ȣ: %d\n", infor_b[index].name_b, infor_b[index].account_b);
    printf("%s���� ���� �ݾ�: %d��\n", infor_b[index].name_b, infor_b[index].money_b);
    Sleep(2500);
}

/* ���¹�ȣ �Է½� �ش��ϴ� ����� �ε��� ���� ã���ִ� �Լ� */
int find_account(client_b *infor_b, int account, int count) {

    for(int i=0; i<count; i++) {
        if(infor_b[i].account_b == account) {
            return i;
        }
        else if(i + 1 == count) {
            printf("�ش��ϴ� ���°� �����ϴ�.");
            return False;
        }
    }
}

/* ������ü �Լ� */
void remittance(client_b *infor_b, int index_a, int count) {
    
    int account, index, money;

        printf("��ü�� ���¹�ȣ �Է�: ");
        scanf("%d", &account);

        index = find_account(infor_b, account, count);
        if(index >= 0) {
            printf("��ü�� �ݾ� �Է�: ");
            scanf("%d", &money);

            infor_b[index_a].money_b -= money;
            infor_b[index].money_b += money;

            printf("��ü �Ϸ�!");
            Sleep(2500);
        }
        else {
            Sleep(1500);
        }
}

/* �Լ����� */
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
                printf("�߸��� ��ȣ�Դϴ�.");
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
                printf("���»����Ϸ�");
                Sleep(2000);
            }
            else if(input_num == 7) {
                exit(0);
            }
            else {
                printf("�߸��� ��ȣ�Դϴ�.");
                Sleep(1000);
            }
        }
    }
}

int main() {

    main_system();
    _getch();
}