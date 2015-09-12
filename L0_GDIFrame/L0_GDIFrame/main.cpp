/*
  Name: L0_GDIFrame
  Author: inksmallfrog
  Refrence: ǳī
  Date: 15.9.13
*/

//--------------------Header----------------------
#include <d3d9.h>
#include <d3dx9.h>
//------------------------------------------------

//----------------------Lib-----------------------
#pragma comment(lib, "winmm.lib")
//------------------------------------------------

//---------------------Macros---------------------
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"L0_GDIFrame"
//------------------------------------------------

//--------------------Functions-------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);       //Window callback func
HRESULT Direct3D_Init(HWND hwnd);
HRESULT Objects_Init(HWND hwnd);
VOID Direct3D_Render(HWND hwnd);
VOID Direct3D_CleanUp();
//------------------------------------------------

//---------------------Global---------------------
//------------------------------------------------

//--------------------WinMain---------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int nCmdShow){
	static LPCWSTR sClassName = L"D3DWindow";

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = sClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wndClass)){
		MessageBox(NULL, L"Register class failed!", L"Fatal!", MB_OK);
		return 1;
	}

	HWND hwnd = CreateWindow(
		sClassName,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (FAILED(Direct3D_Init(hwnd))){
		MessageBox(NULL, L"Init D3D Failed!", L"Fatal!", MB_OK);
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	MoveWindow(hwnd, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, true);
	UpdateWindow(hwnd);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT){
		if (PeekMessage(&msg, NULL, 0, 0, true)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			Direct3D_Render(hwnd);
		}
	}

	UnregisterClass(sClassName, hInstance);
	return msg.wParam;
}
//-------------------------------------------------

//-------------------WndProc-----------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message){
	case WM_PAINT:
		Direct3D_Render(hwnd);
		ValidateRect(hwnd, NULL);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE){
			DestroyWindow(hwnd);
		}
		break;

	case WM_DESTROY:
		Direct3D_CleanUp();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
//--------------------------------------------------

//----------------Direct3D_Init---------------------
HRESULT Direct3D_Init(HWND hwnd){
	return Objects_Init(hwnd);
}
//--------------------------------------------------

//----------------Objects_Init----------------------
HRESULT Objects_Init(HWND hwnd){
	return S_OK;
}
//--------------------------------------------------

//----------------Direct3D_Render-------------------
VOID Direct3D_Render(HWND hwnd){

}
//--------------------------------------------------

//----------------Direct3D_CleanUp------------------
VOID Direct3D_CleanUp(){

}
//--------------------------------------------------