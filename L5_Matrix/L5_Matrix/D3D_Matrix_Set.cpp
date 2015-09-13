#include "D3D_Matrix_Set.h"
#include "D3D_Window.h"

VOID Matrix_Set(LPDIRECT3DDEVICE9 &pd3dDevice){
	D3DXMATRIX matWorld, Rx, Ry, Rz;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&Rx, D3DX_PI * (timeGetTime() / 1000.0f));
	D3DXMatrixRotationY(&Ry, D3DX_PI * (timeGetTime() / 1000.0f / 2));
	D3DXMatrixRotationZ(&Rz, D3DX_PI * (timeGetTime() / 1000.0f / 3));
	matWorld = Rx * Ry * Rz * matWorld;
	pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXMATRIX matView;
	D3DXVECTOR3 vEye(0.0f, 0.0f, -200.0f);
	D3DXVECTOR3 vAt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEye, &vAt, &vUp);
	pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, 1.0f, 1.0f, 1000.0f);
	pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DVIEWPORT9 vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	vp.X = 0;
	vp.Y = 0;
	pd3dDevice->SetViewport(&vp);
}