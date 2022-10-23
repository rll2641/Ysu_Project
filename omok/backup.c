#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define OMOK_LENGTH 19 // �������� ũ�� ����
#define WALL  1        // ��
#define EMPTY 2        // �� ����(���� �����Ӱ� �̵��Ҽ��ִ°���)
#define BLACK 3        // �浹
#define WHITE 4        // �鵹    
#define BLACK_WIN 5    // �浹�� �̰�����
#define WHITE_WIN 6    // �鵹�� �̰�����

int map[OMOK_LENGTH][OMOK_LENGTH]; // ������ �������� ����
const char* stone[2]={"��","��"};     // �浹�� �鵹�� const ����� ����
int stone_x = 2, stone_y = 1, flag = 0; 

void CursorView(char); // Ŀ�� ����� �Լ�
void gotoxy(int,int);  // ���ϴ�x,y��ǥ�� �̵��Ҽ��ִ� �Լ�
void intro();          // ���� ��Ʈ�� �Լ�
void select_menu();     // �޴� ���� �Լ�
void omok();           // �������� ����� �Լ�
void play_omok();       // ����������Ʈ�� �߽��Լ�
void draw_stone();      // ���������� ���� �δ� �Լ� (�÷��� �̿�)
void input_key(char,int*,int*); // ����Ű �Է½� �ƽ�Ű�ڵ尪�� Ȱ���Ͽ� ���� ������
int gameover();        // ����5���Ͻ� �������Ḧ �ϴ� �Լ�.

int main(){

    int test;
    CursorView(0);
    intro();
    play_omok();
    test=_getch();
    return 0;

}

void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}
void gotoxy(int x, int y)
{

COORD pos={x,y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 

}
void intro(){

    printf("###################################################\n");
    printf("#                                                 #\n");
    printf("#                                                 #\n");
    printf("#                     �������                    #\n");
    printf("#                                                 #\n");
    printf("#            1.����                2.����         #\n");
    printf("#                                                 #\n");
    printf("#                                                 #\n");
    printf("#  (������б� ai��ǻ�Ͱ��а� 10191541/������)    #\n");
    printf("###################################################\n");

    select_menu();

}
void select_menu(){

    int input_num = 0;

    while(1){
        
        input_num = _getch() - '0';

        if(input_num == 1){
            system("cls");
            break;
        }
        else if(input_num == 2)
            exit(0);
        else
            continue;
    }

}
void omok(){
    
    int i = 0,j = 0;

    for(i=0; i<OMOK_LENGTH; i++){
        for(j=0; j<OMOK_LENGTH; j++){
            if(i == 0 || i == OMOK_LENGTH-1){
                if(j >=0 || j <= OMOK_LENGTH-1){
                    map[i][j] = WALL;
                    printf("��");
                }
            }
            else if(j == 0 || j == OMOK_LENGTH-1){
                if(i >= 1 || i <= OMOK_LENGTH-2){
                    map[i][j] = WALL;
                    printf("��");
                }
            }
            else if(map[i][j] == BLACK){
                gotoxy(j*2,i);
                printf("%s", stone[0]);
            }
            else if(map[i][j] == WHITE){
                gotoxy(j*2,i);
                printf("%s", stone[1]);
            }
            else{
                map[i][j] = EMPTY;
                printf("��");
            }
        }
        putchar('\n');
    }
       
}
void play_omok(){

    int check_win = 0;

    while(1){
        
        omok(); // ������ ����.
        draw_stone(); // �� ����
        system("cls");
        check_win = gameover();
        if(check_win == BLACK_WIN){
            gotoxy(80,6);
            printf("�浹�� �̰���ϴ� !");
            break;
        }
        else if(check_win == WHITE_WIN){
            gotoxy(80,6);
            printf("�鵹�� �̰���ϴ� !");
            break;
        }
    }
}
void draw_stone(){

    char key = 0;
    
    if(flag == 0){

        gotoxy(stone_x,stone_y);
        printf("%s", stone[flag]);

        key = _getch();

        if(key >= 72){
            input_key(key,&stone_x,&stone_y);
        }
        if(key == 13){
            map[stone_y][stone_x/2] = BLACK;
            stone_x = 2, stone_y = 1;
            flag = 1;
            return;
        }
    }

    if(flag == 1){

        gotoxy(stone_x,stone_y);
        printf("%s", stone[flag]);

        key = _getch();

        if(key >= 72){
            input_key(key,&stone_x,&stone_y);
        }
        if(key == 13){
            map[stone_y][stone_x/2] = WHITE;
            stone_x = 2, stone_y = 1;
            flag = 0;
            return;
        }
    }
}
void input_key(char key,int *x,int *y){

    switch(key){

        case 72:
            *y -= 1;
            break;
        case 75:
            *x -= 2;
            break;
        case 77:
            *x += 2;
            break;
        case 80:
            *y += 1;
        default:
            return;
    
    }
}
int gameover(){

    int i , j, k;
    int count_b=0;
    int count_w=0;

    // ������ �˻�

    for(i=0; i<OMOK_LENGTH; i++){ //������
 
        count_b = 0; //�������� �ٲ����� �ٽ� 0���� �ʱ�ȭ
        count_w = 0;

        for(j=0; j<OMOK_LENGTH; j++){ // ������

            if(map[i][j] == BLACK){ // for���� ���������� ���� �˾Ƴ��� ���ٰ� ù��° black�� ������ +4������ �˻縦�ϸ�ȴ�.
                count_b++;
                if(count_b == 5)
                    return BLACK_WIN;
            }
            if(map[i][j] == WHITE){
                count_w++;
                if(count_w == 5)
                    return WHITE_WIN;
            }
        }
    }

    // ������ �˻�

    for(i=0; i<OMOK_LENGTH; i++){ // ������

        count_b = 0;
        count_w = 0;

        for(j=0; j<OMOK_LENGTH; j++){ // ������

            if(map[j][i] == BLACK){
                count_b++;
                if(count_b == 5)
                    return BLACK_WIN;
            }
            if(map[j][i] == WHITE){
                count_w++;
                if(count_w == 5)
                    return WHITE_WIN;
            }
        }
    }

    // \�밢�� �˻�

    for(i=0; i<OMOK_LENGTH; i++){
        count_b = 0;
        for(j=0; j<OMOK_LENGTH; j++){
            int save_x = j;
            int save_y = i;
            for(int k=0; k<5; k++){
                if(map[save_y++][save_x++] == BLACK){
                    count_b++;
                    if(count_b == 5)
                        return BLACK_WIN;
                }
                else
                    count_b = 0;
            }        
        }
    }

}