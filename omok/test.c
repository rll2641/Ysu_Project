#include <stdio.h>     // printf
#include <conio.h>     // _getch
#include <windows.h>   // system,Sleep등등

/* 전처리기 매크로 상수 설정 */

#define OMOK_LENGTH 19 // 오목판의 크기 설정
#define WALL  1        // 벽
#define EMPTY 2        // 빈 공간(돌이 자유롭게 이동할수있는공간)
#define BLACK 3        // 흑돌
#define WHITE 4        // 백돌    
#define BLACK_WIN 5    // 흑돌이 이겼을때
#define WHITE_WIN 6    // 백돌이 이겼을때

/* 전역변수 */

int map[OMOK_LENGTH][OMOK_LENGTH];      // 오목판 전역변수 설정
const char* stone[2]={"○","●"};         // 흑돌과 백돌을 const 상수로 설정
int stone_x = 2, stone_y = 1, flag = 0; // 현재 돌의 좌표.

/* 함수 원형 선언 */

void CursorView(char); 
void gotoxy(int,int); 
void intro();          
void select_menu();     
void omok();                    
void play_omok();               
void draw_stone();              
void input_key(char,int*,int*); 
int gameover();                 

int main(){

    CursorView(0);
    intro();
    play_omok();
    return 0;

}

/* 커서(키보드입력바)를 숨기는 함수 */

void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

/* 원하는 x,y좌표에 이동하게 만드는 함수 */

void gotoxy(int x, int y)
{

COORD pos={x,y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 

}

 /* 오목게임 인트로 */

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

/* 메뉴판 번호 입력함수 */

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

/* 오목맵을 만드는함수 */

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

/* 돌을 순차적으로 두는 함수 */

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

/*  방향키 입력시 돌을 움직이게 하는 함수 */

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

/* 돌이 연달아 5개일시 게임종료 함수 */

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
        count_w = 0;

        for(j=0; j<OMOK_LENGTH; j++){

            int save_x = j;
            int save_y = i;

            for(k=0; k<5; k++){

                if(map[save_y++][save_x++] == BLACK){
                    count_b++;
                    if(count_b == 5)
                        return BLACK_WIN;
                }

                else if(map[save_y++][save_x++] == WHITE){
                    count_w++;
                    if(count_w == 5)
                        return WHITE_WIN;
                }

                else{
                    count_b = 0;
                    count_w = 0;
                }
            }        
        }
    }

    // /대각선 검사

    for(i=0; i<OMOK_LENGTH; i++){

        count_b = 0;
        count_w = 0;

        for(j=OMOK_LENGTH-1; j>0; j--){

            int save_x1 = j;
            int save_y1 = i;

            for(k=0; k<5; k++){

                if(map[save_y1++][save_x1--] == BLACK){
                    count_b++;
                    if(count_b == 5)
                        return BLACK_WIN;
                }

                else if(map[save_y1++][save_x1--] == WHITE){
                    count_w++;
                    if(count_w == 5)
                        return WHITE_WIN;
                }

                else{
                    count_b = 0;
                    count_w = 0;
                }
            }
        }
    }
}

/* 오목게임의 중점 함수 */

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
            Sleep(3000);
            break;
        }

        else if(check_win == WHITE_WIN){
            gotoxy(80,6);
            printf("백돌이 이겼습니다 !");
            Sleep(3000);
            break;
        }
    }
}