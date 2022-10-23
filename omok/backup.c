#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define OMOK_LENGTH 19 // 오목판의 크기 설정
#define WALL  1        // 벽
#define EMPTY 2        // 빈 공간(돌이 자유롭게 이동할수있는공간)
#define BLACK 3        // 흑돌
#define WHITE 4        // 백돌    
#define BLACK_WIN 5    // 흑돌이 이겼을때
#define WHITE_WIN 6    // 백돌이 이겼을때

int map[OMOK_LENGTH][OMOK_LENGTH]; // 오목판 전역변수 설정
const char* stone[2]={"○","●"};     // 흑돌과 백돌을 const 상수로 설정
int stone_x = 2, stone_y = 1, flag = 0; 

void CursorView(char); // 커서 숨기는 함수
void gotoxy(int,int);  // 원하는x,y좌표로 이동할수있는 함수
void intro();          // 오목 인트로 함수
void select_menu();     // 메뉴 선택 함수
void omok();           // 오목판을 만드는 함수
void play_omok();       // 오목프로젝트의 중심함수
void draw_stone();      // 순차적으로 돌을 두는 함수 (플래그 이용)
void input_key(char,int*,int*); // 방향키 입력시 아스키코드값을 활용하여 돌을 움직임
int gameover();        // 돌이5개일시 게임종료를 하는 함수.

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
    printf("#                     오목게임                    #\n");
    printf("#                                                 #\n");
    printf("#            1.시작                2.종료         #\n");
    printf("#                                                 #\n");
    printf("#                                                 #\n");
    printf("#  (영산대학교 ai컴퓨터공학과 10191541/조지훈)    #\n");
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
                    printf("■");
                }
            }
            else if(j == 0 || j == OMOK_LENGTH-1){
                if(i >= 1 || i <= OMOK_LENGTH-2){
                    map[i][j] = WALL;
                    printf("■");
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
                printf("□");
            }
        }
        putchar('\n');
    }
       
}
void play_omok(){

    int check_win = 0;

    while(1){
        
        omok(); // 오목판 생성.
        draw_stone(); // 돌 생성
        system("cls");
        check_win = gameover();
        if(check_win == BLACK_WIN){
            gotoxy(80,6);
            printf("흑돌이 이겼습니다 !");
            break;
        }
        else if(check_win == WHITE_WIN){
            gotoxy(80,6);
            printf("백돌이 이겼습니다 !");
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

    // 가로줄 검사

    for(i=0; i<OMOK_LENGTH; i++){ //세로줄
 
        count_b = 0; //세로줄이 바꼈을때 다시 0으로 초기화
        count_w = 0;

        for(j=0; j<OMOK_LENGTH; j++){ // 가로줄

            if(map[i][j] == BLACK){ // for문은 순차적으로 값을 알아낸다 가다가 첫번째 black이 있으면 +4까지만 검사를하면된다.
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

    // 세로줄 검사

    for(i=0; i<OMOK_LENGTH; i++){ // 가로줄

        count_b = 0;
        count_w = 0;

        for(j=0; j<OMOK_LENGTH; j++){ // 세로줄

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

    // \대각선 검사

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