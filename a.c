#include <windows.h>

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static HDC backHDC; // back → 背景のＨＤＣ
static HBITMAP backBMP; // back → 背景のＢＭＰ
static HDC markHDC; // マークを読み込む変数ＨＤＣ
static HBITMAP markBMP; // マークを読み込む変数ＢＭＰ
HDC hdc;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
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

LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
TCHAR tcStr[128];
static int keyA; // キーを押した？（１：はい、０：いいえ）
static int keyS;
static int keyD;
static int keyW;
static int jibunX; // 自分のＸＹ座標を設定
static int jibunY;
switch(Msg)
{
// ＥＸＥを起動したらここが最初に実行される
case WM_CREATE:
hdc=GetDC(hWnd);
// 背景を読み込む
backHDC = CreateCompatibleDC(hdc); // メモリを確保？
backBMP = (HBITMAP)LoadImage(NULL,"back.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE); // ＨＤＤの画像を読み込む
SelectObject(backHDC,backBMP); // ２つを連結？
// マークを読み込む
markHDC = CreateCompatibleDC(hdc); // メモリを確保？
markBMP = (HBITMAP)LoadImage(NULL,"mark.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE); // ＨＤＤの画像を読み込む
SelectObject(markHDC,markBMP); // ２つを連結？
ReleaseDC(hWnd, hdc);
jibunX=300; // 自分のＸＹ座標を設定
jibunY=200;
// タイマーを１００ミリ秒に設定
SetTimer(hWnd,NULL,100,NULL); // 今回入れる物が無いのでＮＵＬＬで埋めている
keyA=0; // フラグを下げておく
keyS=0;
keyD=0;
keyW=0;
break;
case WM_DESTROY:
PostQuitMessage(0);
return 0;
// キーを押した
case WM_KEYDOWN:
if(wParam=='A')keyA=1; //キーを押したらフラグを立てる
if(wParam=='S')keyS=1;
if(wParam=='D')keyD=1;
if(wParam=='W')keyW=1;
break;
// キーを放した
case WM_KEYUP:
if(wParam=='A')keyA=0; // キーを放したらフラグを下ろす
if(wParam=='S')keyS=0;
if(wParam=='D')keyD=0;
if(wParam=='W')keyW=0;
break;

// ゲームのメイン処理
// １００ミリ秒ごとに何度も実行される（すなわちコイツがwhileの代わりになる）
case WM_TIMER:
// キー入力処理
if(keyA==1)jibunX-=10; // キーを押したら上下左右に動く
if(keyS==1)jibunY+=10;
if(keyD==1)jibunX+=10;
if(keyW==1)jibunY-=10;
//表示処理
hdc=GetDC(hWnd);
BitBlt(hdc, 0, 0,640,360,backHDC,0,0,SRCCOPY); // 背景を表示
BitBlt(hdc,jibunX,jibunY,105, 35,markHDC,0,0,SRCCOPY); // マークを表示（上下左右に動く）
ReleaseDC(hWnd, hdc);
break;
	
// ×ボタンを押して終了する際はここが実行される
case WM_CLOSE:
// 終了前に破棄する
DeleteDC (backHDC); // 追加
DeleteObject(backBMP); // 追加
DeleteDC (markHDC); // 追加
DeleteObject(markBMP); // 追加
PostQuitMessage(0);
break;
}
return DefWindowProc(hWnd , Msg , wParam , lParam);
}
