#include "bank_menu.h"
#include "bank_signup.h"
#include "bank_function.h"

void main() {
	Client client[Max_Client];
	FILE* fp = NULL;
	int index,input_num = 0;

	while (True) {
		while (True) {
			system("cls");
			menu();
			input_num = _getch() - '0';
			if (input_num == 1) {
				index = login(fp);
				break;
			}
			else if (input_num == 2) {
				signup(client, fp);
				continue;
			}
			else if (input_num == 3) {
				exit(0);
			}
			else {
				continue;
			}
		}

		while (True) {
			system("cls");
			menu2();
			input_num = _getch() - '0';
			if (input_num == 1) {
				deposit(fp, index);
				continue;
			}
			else if (input_num == 2) {
				withdraw(fp, index);
				continue;
			}
			else if (input_num == 3) {
				track_account(fp, index);
				continue;
			}
			else if (input_num == 4) {
				remittance(fp, index);
				continue;
			}
			else if (input_num == 5) {
				break;
			}
			else if (input_num == 6) {
				exit(0);
			}
			else {
				continue;
			}
		}
	}
}