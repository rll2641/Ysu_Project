#include "bank_menu.h"
#include "bank_signup.h"

/* �� �� */
int count = 0;

/* �ߺ��˻� */
int examine_overlap(Client* client, FILE* fp) {

    Client save[Max_Client];
    int num = 0;

    fp = fopen(File_Name, "rb");
    num = fread(save, sizeof(Client), Max_Client, fp);

    for (int j = 0; j < num; j++) {
        // ���̵�� ����ȣ�� ���� �� True ��ȯ ������ False ��ȯ
        if (strcmp(client[count].id, save[j].id) == 0 || strcmp(client[count].phone, save[j].phone) == 0) {
            fclose(fp);
            return True;
        }
        else {
            fclose(fp);
            return False;
        }
    }
    fclose(fp);
    return False;
}

/* ���»��� */
void create_account(Client* client) {

    srand(time(NULL));
    client[count].account = rand();
    client[count].money = 0;
}

/* ȸ������ */
void signup(Client* client, FILE* fp) {

    fp = fopen(File_Name, "ab");

    while (True) {
        system("cls");
        printf("Name: ");
        scanf("%s", client[count].name);
        printf("Phone-Number: ");
        scanf("%s", client[count].phone);
        printf("Id: ");
        scanf("%s", client[count].id);
        printf("Password: ");
        scanf("%s", client[count].pw);
        if (examine_overlap(client, fp)) {
            printf("\n\nId or Phone-Number is overlap!");
            Sleep(1500);
            continue;
        }
        else {
            printf("\n\nSignup Complete!");
            Sleep(1500);
            break;
        }
        break;
    }
    create_account(client);

    fwrite(client, sizeof(Client), 1, fp);
    fclose(fp);

    count++;
}

/* �α��� */
int login(FILE* fp) {

    Client save[Max_Client];
    char id[Length] = { 0 };
    char pw[Length] = { 0 };
    int num = 0;

    fp = fopen(File_Name, "rb");
    num = fread(save, sizeof(Client), Max_Client, fp);

    while (True) {
        system("cls");
        printf("Id: ");
        scanf("%s", id);
        printf("Password: ");
        scanf("%s", pw);

        for (int j = 0; j < num; j++) {
            if (strcmp(id, save[j].id) == 0 && strcmp(pw, save[j].pw) == 0) {
                printf("\n\nUser confirm!");
                Sleep(1500);
                fclose(fp);
                return j;
            }
            else if (j + 1 == num) {
                printf("\n\nId or Password Wrong!");
                Sleep(1500);
                fclose(fp);
                break;
            }
        }
    }
}