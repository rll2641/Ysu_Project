#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

// ȸ�����Խ� �ִ� ���� ��
#define limit 8
// �ð� ����
#define hour 1
#define thour 2

// �޴� â
void print_menu();
// �޴� �Լ�
void menu();
// ȸ������ �Լ�
char *signup_id();
char *signup_pw();
// �α��� �Լ�
char *login_id();
char *login_pw();
// �ð� ���� �Լ�
int select_time();
// �����ð� Ȯ�� �Լ�
void check_time();

int main(){

    menu();
    return 0;
}

void print_menu(){

    printf("##################################################\n");
    printf("##                                              ##\n");
    printf("##           (�α��� �� ȸ������ �ʼ�!)         ##\n");
    printf("##          1.�α��� 2.ȸ������ 3.pc����        ##\n");
    printf("##                                              ##\n");
    printf("##                                              ##\n");
    printf("##       ������б� 10191541/ai�İ�/������      ##\n");
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
                    printf("�α��� ��\n");
                    Sleep(2000);
                    printf("ȸ�������� ��ġ�մϴ�.\n");
                    Sleep(2000);
                    free(id);free(id2);free(pw);free(pw2);
                    system("cls");
                    check_time();
                }
                else{
                    system("cls");
                    printf("���̵� ��й�ȣ�� �ٽ� Ȯ�����ּ���.\n");
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

    printf("���̵�,��й�ȣ�� ���� �ҹ���,������ �������� �ִ� 8���ڱ��� �����մϴ�.\n");
    printf("���̵� �Է�: ");
    gets(id);
    printf("����� ���̵� Ȯ��: %s\n", id);
    Sleep(1500);

    return id;
}

char *signup_pw(){

    char *pw = (char*)malloc(limit + 1);

    printf("��й�ȣ �Է�: ");
    gets(pw);
    printf("����� ��й�ȣ Ȯ��: %s\n", pw);
    Sleep(1500);
    printf("ȸ�����ԿϷ�!\n");
    Sleep(1500);
    system("cls");

    return pw;
}

char *login_id(){

    char *id = (char*)malloc(limit + 1);

    printf("���̵�: ");
    gets(id);

    return id;
}

char *login_pw(){

    char *pw = (char*)malloc(limit + 1);

    printf("��й�ȣ:");
    gets(pw);

    return pw;
}

int select_time(){

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    int num;

    printf("���Ͻô� �ð��� ���� ���ּ���.\n");
    printf("�ش� �ð��� ������ �ڵ������� ��ǻ�Ͱ� �����ϰ� �˴ϴ�.\n");
    printf("[1. 1�ð� / 2. 2�ð�]\n");

    num = _getch() - '0';

    if (num == 1){
        system("cls");
        printf("1�ð� ���ÿϷ�\n");
        printf("���ݺ��� 1�ð��ڿ� �ڵ������� ��ǻ�Ͱ� ������ �˴ϴ�.\n");
        printf("���� �ð�: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("���� �ð�: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour+1, tm.tm_min, tm.tm_sec);
        Sleep(5000);
        system("cls");
        return hour;
    }
    else if (num == 2){
        system("cls");
        printf("2�ð� ���ÿϷ�\n");
        printf("���ݺ��� 2�ð��ڿ� �ڵ������� ��ǻ�Ͱ� ������ �˴ϴ�.\n");
        printf("���� �ð�: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("���� �ð�: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour+2, tm.tm_min, tm.tm_sec);
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
            printf("�����ð�: %d:%d:%d\n", t/3600, (t%3600)/60, (t%3600)%60);
            t--;
            Sleep(1000);
            system("cls");
        }
        system("shutdown -s -t 1");
    }
    else if(check == thour){
        t = 7200;
        while(t>0){
            printf("�����ð�: %d:%d:%d\n", t/3600, (t%3600)/60, (t%3600)%60);
            t--;
            Sleep(1000);
            system("cls");
        }
        system("shutdown -s -t 1");
    }
}