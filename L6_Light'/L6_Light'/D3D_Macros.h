#ifndef _H_D3D_MACROS_
#define _H_D3D_MACROS_

#include "D3D_Window_Macros.h"

#define HR(p) if(FAILED(p)){return E_FAIL;}
#define SAFE_RELEASE(p) if(NULL != (p)){(p)->Release(); (p) = NULL;}

#endif