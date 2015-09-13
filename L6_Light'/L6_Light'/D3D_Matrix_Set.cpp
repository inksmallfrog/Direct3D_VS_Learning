#include "D3D_Matrix_Set.h"
#include "D3D_Window_Macros.h"

VOID Matrix_Set(LPDIRECT3DDEVICE9 &pd3dDevice){
	D3DXMATRIX matView;
	D3DXVECTOR3 vEye(0.0f, 0.0f, -80.0f);
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
	vp.MinZ = 0;
	vp.MaxZ = 1;
	vp.X = 0;
	vp.Y = 0;
	pd3dDevice->SetViewport(&vp);
}
