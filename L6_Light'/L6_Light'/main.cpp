/*
  Name: D3D_Program
  Author: inksmallfrog
  Date: 15.9.13
*/

//--------------------Header----------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include "D3D_Macros.h"
#include "D3D_Info.h"
#include "D3D_Matrix_Set.h"
#include "D3D_Light_Set.h"
//------------------------------------------------

//----------------------Lib-----------------------
#pragma comment(lib, "winmm.lib")
//------------------------------------------------

//--------------------Functions-------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);       //Window callback func
HRESULT Direct3D_Init(HWND hwnd);
HRESULT Objects_Init(HWND hwnd);
VOID Direct3D_Render(HWND hwnd);
VOID Direct3D_CleanUp();
//------------------------------------------------

//---------------------Global---------------------
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
D3DXMATRIX g_World[4];
ID3DXMesh *g_pCube = NULL;
ID3DXMesh *g_pSphere = NULL;
ID3DXMesh *g_pTorus = NULL;
ID3DXMesh *g_pTeapot = NULL;
ID3DXFont *g_pFont = NULL;
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
	LPDIRECT3D9 pD3d = NULL;
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION))){
		return E_FAIL;
	}

	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(caps));
	HR(pD3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps));
	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT){
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.Flags = 0;

	HR(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &d3dpp, &g_pd3dDevice));
	SAFE_RELEASE(pD3d);

	return Objects_Init(hwnd);
}
//--------------------------------------------------

//----------------Objects_Init----------------------
HRESULT Objects_Init(HWND hwnd){
	HR(D3DXCreateFont(g_pd3dDevice, 26, 0, 0, 0, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"微软雅黑", &g_pFont));

	HR(D3DXCreateBox(g_pd3dDevice, 6.0f, 6.0f, 6.0f, &g_pCube, NULL));
	HR(D3DXCreateSphere(g_pd3dDevice, 3.0f, 10, 10, &g_pSphere, NULL));
	HR(D3DXCreateTorus(g_pd3dDevice, 1.5f, 3.0f, 10, 10, &g_pTorus, NULL));
	HR(D3DXCreateTeapot(g_pd3dDevice, &g_pTeapot, NULL));

	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	mtrl.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	mtrl.Specular = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	g_pd3dDevice->SetMaterial(&mtrl);

	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pd3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	Light_Set(g_pd3dDevice, 0);

	return S_OK;
}
//--------------------------------------------------

//----------------Direct3D_Render-------------------
VOID Direct3D_Render(HWND hwnd){
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	RECT windowRect;
	GetClientRect(hwnd, &windowRect);

	wchar_t sFPS[50];
	int nFPSLength = swprintf_s(sFPS, 50, L"FPS: %0.3f", Get_FPS());

	D3DXMATRIX Ry;
	D3DXMatrixRotationY(&Ry, D3DX_PI * (timeGetTime() / 2000.0f));

	Matrix_Set(g_pd3dDevice);

	//key Q 
	if (GetAsyncKeyState(0x51) & 0x8000f){
		Light_Set(g_pd3dDevice, 0);
	}
	//key W
	if (GetAsyncKeyState(0x45) & 0x8000f){
		Light_Set(g_pd3dDevice, 1);
	}
	//key E
	if (GetAsyncKeyState(0x57) & 0x8000f){
		Light_Set(g_pd3dDevice, 2);
	}

	g_pd3dDevice->BeginScene();

	D3DXMatrixTranslation(&g_World[0], -10.0f, 10.0f, 0.0f);
	g_World[0] *= Ry;
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &g_World[0]);
	g_pCube->DrawSubset(0);

	D3DXMatrixTranslation(&g_World[1], 10.0f, 10.0f, 0.0f);
	g_World[1] *= Ry;
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &g_World[1]);
	g_pSphere->DrawSubset(0);

	D3DXMatrixTranslation(&g_World[2], -10.0f, -10.0f, 0.0f);
	g_World[2] *= Ry;
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &g_World[2]);
	g_pTorus->DrawSubset(0);

	D3DXMatrixTranslation(&g_World[3], 10.0f, -10.0f, 0.0f);
	g_World[3] *= Ry;
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &g_World[3]);
	g_pTeapot->DrawSubset(0);

	//Draw FPS
	g_pFont->DrawText(NULL, sFPS, nFPSLength, &windowRect, DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255)); 

	g_pd3dDevice->EndScene();

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
//--------------------------------------------------

//----------------Direct3D_CleanUp------------------
VOID Direct3D_CleanUp(){
	SAFE_RELEASE(g_pCube);
	SAFE_RELEASE(g_pSphere);
	SAFE_RELEASE(g_pTorus);
	SAFE_RELEASE(g_pTeapot);
	SAFE_RELEASE(g_pFont);
	SAFE_RELEASE(g_pd3dDevice);
}
//--------------------------------------------------