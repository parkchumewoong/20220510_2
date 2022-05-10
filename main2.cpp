#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

#define UK 0xe048 //up방향키
#define RK 0xe04d //right 방향키
#define LK 0xe04b //left 방향키
#define DK 0xe050 //down 방향키
#define ESC 0x11b



//콘솔화면에서 커서의 위치를 변경해주는 함수 퍼왔습니다.
void fnd_gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


//키보드 입력을 받는 함수 getch()함수로 방향키 잡아주는 함수를 퍼왔습니다.
int fnd_GetBKey() {
    int key;
    key = _getch();
    if (key) {
        if (key == 27) {
            return 0x11b;
        }
        if (key == 0xe0) {
            int k2;
            k2 = _getch();
            key = (key << 8) | k2;
        }
        return key;
    }
    else {
        key = _getch();
        key = key << 8;
        return key;
    }
    return key;
}

// 그냥 기본 맵 그리는 printf함수에요..
void fn_MapPrint()
{
    fnd_gotoxy(0, 0);
    printf("움직여 보자");
    fnd_gotoxy(0, 1);
    printf("□□□□□□□□□□□□\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□                    □\n");
    printf("□□□□□□□□□□□□\n");
}


int main2()
{
    // int com;
    char Obj[3] = "●"; //움직일 문자
    char ObjDel[3] = "  ";//움직일 문자를 지우기 위해 공란으로 체우기 위한 문자
    COORD Cur, CurTemp, SPos, LPos, NomalPos;
    //맵에서 하얀부분의 왼쪽 상위 좌표
    SPos.X = 2;
    SPos.Y = 2;

    //맵에서 하얀부분의 오른쪽 하위 좌표
    LPos.X = 20;
    LPos.Y = 11;

    //깜빡이는 커서와 종료 메시지를 뛰울 좌표
    NomalPos.X = 0;
    NomalPos.Y = 24;


    //현제 객체가 있는 좌표
    Cur.X = 2;
    Cur.Y = 2;

    //이동한 좌표
    CurTemp.X = 2;
    CurTemp.Y = 2;


    // 기본 맵 화면에 출력
    fn_MapPrint();

    //처음 문자가 있는 곳에 문자를 출력
    fnd_gotoxy(Cur.X, Cur.Y);
    printf("%s", Obj);

    //다시 깜빡이는 기본 커서 위치로 이동
    fnd_gotoxy(NomalPos.X, NomalPos.Y);

    while (1)
    {
        switch (fnd_GetBKey())
        {
        case UK:
        {
            //up키 클릭시 y좌표를 위로 이동 시켜 줍니다.
            CurTemp.Y = CurTemp.Y - 1;

            //이동 가능 범위 인지 판단
            if (CurTemp.Y >= SPos.Y)
            {
                //현제 위치에 문자를 지웁니다.
                fnd_gotoxy(Cur.X, Cur.Y);
                printf("%s", ObjDel);
                //이동 위치에 문자를 그려줍니다.
                fnd_gotoxy(CurTemp.X, CurTemp.Y);
                printf("%s", Obj);

                //이동한 위치의 좌표를 현제 좌표에 넣어 줍니다.
                Cur.Y = CurTemp.Y;
            }
            else
            {
                //이동이 불가능하므로 이동 좌표를 현제 좌표로 다시 복구 시켜 줍니다.
                CurTemp.Y = Cur.Y;
            }
        }
        break;
        case RK:
        {
            CurTemp.X = CurTemp.X + 2;
            if (CurTemp.X <= LPos.X)
            {
                fnd_gotoxy(Cur.X, Cur.Y);
                printf("%s", ObjDel);
                fnd_gotoxy(CurTemp.X, CurTemp.Y);
                printf("%s", Obj);
                Cur.X = CurTemp.X;
            }
            else
            {
                CurTemp.X = Cur.X;
            }
        }
        break;
        case LK:
        {
            CurTemp.X = CurTemp.X - 2;
            if (CurTemp.X >= SPos.X)
            {
                fnd_gotoxy(Cur.X, Cur.Y);
                printf("%s", ObjDel);
                fnd_gotoxy(CurTemp.X, CurTemp.Y);
                printf("%s", Obj);
                Cur.X = CurTemp.X;
            }
            else
            {
                CurTemp.X = Cur.X;
            }
        }
        break;
        case DK:
        {
            CurTemp.Y = CurTemp.Y + 1;
            if (CurTemp.Y <= LPos.Y)
            {
                fnd_gotoxy(Cur.X, Cur.Y);
                printf("%s", ObjDel);
                fnd_gotoxy(CurTemp.X, CurTemp.Y);
                printf("%s", Obj);
                Cur.Y = CurTemp.Y;
            }
            else
            {
                CurTemp.Y = Cur.Y;
            }
        }
        break;
        case ESC:
        {
            fnd_gotoxy(NomalPos.X, NomalPos.Y);
            printf("종료\n");
            return 0;
        }
        break;
        }
        fnd_gotoxy(NomalPos.X, NomalPos.Y);
    }
    return 0;
}