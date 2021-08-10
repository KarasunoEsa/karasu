#include <windows.h>

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
hWnd = CreateWindow("SAMPLE", "さんぷる" , WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100 , 100 , 800 , 600 , NULL , NULL , NULL , NULL);

while(GetMessage(&msg , hWnd , 0 , 0) > 0)
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}
return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
switch(uMsg)
{
// Ａを押したら音が鳴る
case WM_KEYDOWN:
if(wParam=='A')MessageBeep(MB_OK);
break;
// ×ボタンを押して終了する際はここが実行される
case WM_CLOSE:
PostQuitMessage(0);
break;
}
return DefWindowProc(hWnd , uMsg , wParam , lParam);
}
