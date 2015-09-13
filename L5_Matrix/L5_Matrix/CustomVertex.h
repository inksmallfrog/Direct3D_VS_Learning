#ifndef _H_CUSTOMVERTEX_
#define _H_CUSTOMVERTEX_

#include <d3d9.h>

struct CustomVertex{
	float x, y, z;
	DWORD color;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#endif