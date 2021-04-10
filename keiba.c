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
    int ws = 0; //while stopの略
    int data1 = 4;
    int uma1 = 0;  //馬１のX座標を０に設定（一番左端からスタート）
    int uma2 = 0;  //馬２のX座標を０に設定（一番左端からスタート）
    int uma3 = 0;  //馬３のX座標を０に設定（一番左端からスタート）
    int b; //ランダム選択用
    int atari;
    char key;
    srand(time(NULL));
    printf("ダービー\n");
    printf("■■予想■■\n\n");
    printf("Ｚ・Ｘキー：上下の選択\tスペース：レーススタート");
    karasuxy(1,4); printf("・馬１");
    karasuxy(1,5); printf("・馬２");
    karasuxy(1,6); printf("・馬３");
    while(ws==0) {
        karasuxy(8,data1); printf("←");
        if(kbhit()) {
            key = getch();
        } else key = 0; 
        if(key == 'x')  {
            karasuxy(8,data1); printf("  ");
            data1++;
            if(data1 == 7) {
                karasuxy(8,data1); printf("  ");
                data1 = 4;
                karasuxy(8,data1); printf("←");
            }
        }
        if(key == 'z') {
            karasuxy(8,data1); printf("  ");
            data1--;
            if(data1 == 3) {
                karasuxy(8,data1); printf("  ");
                data1 = 6;
                karasuxy(8,data1); printf("←");
            }
        }
        if(key == ' ') {
            ws = 1;   //レーススタート
        }
    }
    ws = 0;
    Sleep(2500);   //レースを始める前に2.5秒ほど停止
    while(ws == 0) {
        //■馬を動かす前にすべての馬を先に消しておく
        //馬１を消す
        karasuxy(uma1,9);printf(" ");    //(uma1,2)の地点の画像を消す（スペースで塗り替える）
        //馬２を消す
        karasuxy(uma2,10);printf(" ");    //(uma2,3)の地点の画像を消す（スペースで塗り替える）
        //馬３を消す
        karasuxy(uma3,11);printf(" ");    //(uma2,3)の地点の画像を消す（スペースで塗り替える）
        //どの馬を動かすかをランダムで決める
        b = rand()%10;
        switch(b) {
        case 0: uma1++; break;    //馬１を動かす
        case 1: uma2++; break;    //馬２を動かす
        case 2: uma3++; break;    //馬３を動かす
        }
        //ゴールの線を引く
        karasuxy(50,9);printf("|");  //(50,2)の地点にゴールの線を描画
        karasuxy(50,10);printf("|");  //(50,3)の地点にゴールの線を描画
        karasuxy(50,11);printf("|");  //(50,4)の地点にゴールの線を描画
        //馬１を描画
        karasuxy(uma1,9);printf("◆");  //(uma1,2)の地点に馬を描画
        karasuxy(uma2,10);printf("●");  //(uma2,3)の地点に馬を描画
        karasuxy(uma3,11);printf("■");  //(uma3,4)の地点に馬を描画
        //ゲームが速すぎるので人工的にフリーズを発生させる
        Sleep(20);
        if(uma1==50) ws=1;
        else if(uma2==50) ws=2;
        else if(uma3==50) ws=3;
    }
    //■レースが終わってwhileが終わったあとにチェックする
    //atari＝０：予想ハズレ、１：予想アタリ
    atari = 0;  //まずはハズレにしておく
    if(ws==1 && data1==4) atari=1;    //アタリに変更
    if(ws==2 && data1==5) atari=1;    //アタリに変更
    if(ws==3 && data1==6) atari=1;    //アタリに変更
    //どれか１つでも"アタリ"がヒットしたら”アタリ”と表示
    if(atari==0) MessageBox(NULL,"ハズレ","結果",MB_OK);
    if(atari==1) MessageBox(NULL,"アタリ","結果",MB_OK);
    
    getch();
    return 0;
}
