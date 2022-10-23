#include "bank_menu.h"
#include "bank_signup.h"

void deposit(FILE *fp, int index) {

	Client save[Max_Client];
	int money, num = 0;

	fp = fopen(File_Name, "rb");
	num = fread(save, sizeof(Client), Max_Client, fp);
	fclose(fp);

	printf("Enter deposit amount: ");
	scanf("%d", &money);

	save[index].money += money;
	
	fp = fopen(File_Name, "wb");
	fwrite(save, sizeof(Client), num, fp);
	fclose(fp);

	printf("%s money: %d\n", save[index].name, save[index].money);
	
	Sleep(1500);
}

void withdraw(FILE* fp, int index) {

	Client save[Max_Client];
	int money, num = 0;

	fp = fopen(File_Name, "rb");
	num = fread(save, sizeof(Client), Max_Client, fp);
	fclose(fp);

	printf("Enter withdraw amount: ");
	scanf("%d", &money);

	save[index].money -= money;

	fp = fopen(File_Name, "wb");
	fwrite(save, sizeof(Client), num, fp);
	fclose(fp);

	printf("%s money: %d\n", save[index].name, save[index].money);
	Sleep(1500);
}

void track_account(FILE* fp, int index) {

	Client save[Max_Client];
	
	fp = fopen(File_Name, "rb");
	fread(save, sizeof(Client), Max_Client, fp);

	printf("%s account_number: %d\n", save[index].name, save[index].account);
	printf("%s money: %d\n", save[index].name, save[index].money);
	fclose(fp);
	Sleep(2000);

}

int find_account(FILE* fp, int account) {

	Client save[Max_Client];
	int num = 0;

	fp = fopen(File_Name, "rb");
	num = fread(save, sizeof(Client), Max_Client, fp);

	for (int i = 0; i < num; i++) {
		if (account == save[i].account) {
			fclose(fp);
			return i;
		}
		else if(i + 1 == num) {
			printf("Can't find account number!");
			fclose(fp);
		}
	}
}

void remittance(FILE* fp,int index) {

	Client save[Max_Client];
	int account,index2,money,num = 0;

	printf("Enter the account number: ");
	scanf("%d", &account);

	index2 = find_account(fp, account);

	fp = fopen(File_Name, "rb");
	num = fread(save, sizeof(Client), Max_Client, fp);
	fclose(fp);

	printf("Enter the amount to transfer: ");
	scanf("%d", &money);

	save[index].money -= money;
	save[index2].money += money;

	fp = fopen(File_Name, "wb");
	fwrite(save, sizeof(Client), num, fp);
	fclose(fp);

	printf("remittance complete!");
	fclose(fp);
	Sleep(2000);
}