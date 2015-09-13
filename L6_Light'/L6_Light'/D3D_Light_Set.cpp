#include "D3D_Light_Set.h"

VOID Light_Set(LPDIRECT3DDEVICE9 &pd3dDevice, UINT uType){
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));

	switch (uType){
	case 0:
		light.Type = D3DLIGHT_POINT;
		light.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		light.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		light.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		light.Position = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		light.Range = 300.0f;
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;
		break;

	case 1:
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		light.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		light.Direction = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		break;

	case 2:
		light.Type = D3DLIGHT_SPOT;
		light.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		light.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		light.Specular = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		light.Position = D3DXVECTOR3(0.0f, -100.0f, 0.0f);
		light.Direction = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		light.Range = 300.0f;
		light.Falloff = 0.1f;
		light.Phi = D3DX_PI / 3.0f;
		light.Theta = D3DX_PI / 6.0f;
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;
		break;

	default:
		break;
	}

	pd3dDevice->SetLight(0, &light);
	pd3dDevice->LightEnable(0, true);
	pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(36, 36, 36));
}
