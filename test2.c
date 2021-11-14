#include <windows.h>

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, int nCmdShow)
{
HWND hWnd;
WNDCLASS wc;
MSG msg;

// 構造体を使ってウインドウクラスを宣言する
wc.style = 0;
wc.cbClsExtra = 0;
wc.cbWndExtra = 0;
wc.hInstance = 0;
wc.hIcon = 0;
wc.hCursor = 0;
wc.lpszMenuName = 0;
wc.lpfnWndProc = WindowProc;
wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1; // ウインドウの色
wc.lpszClassName = "SAMPLE"; // このウインドウクラスに名前を付ける
// ウインドクラスの登録
RegisterClass(&wc);

// ウインドウを作る
hWnd = CreateWindow("SAMPLE", "サンプル" , WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100 , 100 , 800 , 600 , NULL , NULL , NULL , NULL);

while(GetMessage(&msg , hWnd , 0 , 0) > 0)
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}
return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
static HDC backHDC; // back → 背景のＨＤＣ
static HBITMAP backBMP; // back → 背景のＢＭＰ
static HDC markHDC; // マークを読み込む変数ＨＤＣ
static HBITMAP markBMP; // マークを読み込む変数ＢＭＰ
HDC hdc;
static int jibunX; // 自分のＸＹ座標
static int jibunY;

switch(uMsg)
{
// ×ボタンを押して終了する際はここが実行される
case WM_CLOSE:
// 終了前に破棄する
DeleteDC (backHDC); // 追加
DeleteObject(backBMP); // 追加
DeleteDC (markHDC); // 追加
DeleteObject(markBMP); // 追加
PostQuitMessage(0);
break;
// ＥＸＥを起動したらここが最初に実行される
case WM_CREATE:
hdc=GetDC(hWnd);
// 背景を読み込む
backHDC = CreateCompatibleDC(hdc);
backBMP = (HBITMAP)LoadImage(NULL,"back.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
SelectObject(backHDC,backBMP);
// マークを読み込む
markHDC = CreateCompatibleDC(hdc);
markBMP = (HBITMAP)LoadImage(NULL,"mark.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
SelectObject(markHDC,markBMP);
ReleaseDC(hWnd, hdc);
SetTimer(hWnd,NULL,100,NULL); // タイマーを１００ミリ秒に設定
jibunX=300; // 自分のＸＹ座標を設定
jibunY=200;
break;
// １００ミリ秒ごとにここが実行される
case WM_TIMER:
if((GetKeyState('A')&0x80) == 0x80)jibunX-=10; // キーを押したら移動
if((GetKeyState('S')&0x80) == 0x80)jibunY+=10;
if((GetKeyState('D')&0x80) == 0x80)jibunX+=10;
if((GetKeyState('W')&0x80) == 0x80)jibunY-=10;
hdc=GetDC(hWnd);
BitBlt(hdc, 0, 0,640,360,backHDC,0,0,SRCCOPY); // 背景を表示
BitBlt(hdc,jibunX,jibunY,105, 35,markHDC,0,0,SRCCOPY); // マークを表示
ReleaseDC(hWnd, hdc);
break;
}
return DefWindowProc(hWnd , uMsg , wParam , lParam);
}
