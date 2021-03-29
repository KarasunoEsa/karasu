#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
// ■自作関数：画面の好きな位置に文字が書けるようになる
void karasuxy(int x,int y) {
    HANDLE hCOut;
    COORD Coord;
    hCOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Coord.X = (SHORT)x;
    Coord.Y = (SHORT)y;
    SetConsoleCursorPosition(hCOut, Coord);
}
int main() {
    int a = 0;//whileのループ条件
    int uma1 = 0;//馬１のX座標を０に設定（一番左端からスタート）
    int uma2 = 0;//馬２のX座標を０に設定（一番左端からスタート）
    int b;//ランダム選択用
    srand(time(NULL));
    printf("■カラスのダービー\n");
    while(a == 0) {
        //■馬を動かす前にすべての馬を先に消しておく
        //馬１を消す
        karasuxy(uma1,2);printf(" "); //(uma1,2)の地点の画像を消す（スペースで塗り替える）
        //馬２を消す
        karasuxy(uma2,3);printf(" "); //(uma2,3)の地点の画像を消す（スペースで塗り替える）
        //どの馬を動かすかをランダムで決める
        b = rand()%10;
        switch(b) {
        case 0: uma1++; break;//馬１を動かす
        case 1: uma2++; break;//馬２を動かす
        }
        //ゴールの線を引く
        karasuxy(50,2);printf("|");//(40,2)の地点にゴールの線を描画
        karasuxy(50,3);printf("|");//(40,2)の地点にゴールの線を描画
        //馬１を描画
        karasuxy(uma1,2);printf("◆");//(uma1,2)の地点に馬を描画
        karasuxy(uma2,3);printf("◇");//(uma2,3)の地点に馬を描画
        //ゲームが速すぎるので人工的にフリーズを発生させる
        Sleep(20);
        if(uma1 == 50 || uma2 == 50){
            printf("\n\nゴール");
            MessageBeep(MB_OK);
        }
        //両方の馬が50を超えたとき、脱出し動きを停止
        if(uma1 ==  50 || uma2 == 50) a = 1;
    }
    getch();
    return 0;
}
