#ifndef _H_CUSTOMVERTEX_
#define _H_CUSTOMVERTEX_

#include <d3d9.h>

struct CustomVertex{
	float x, y, z, rhw;
	DWORD color;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#endif 