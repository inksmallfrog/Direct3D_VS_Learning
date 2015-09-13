#include "D3D_Info.h"
#include "d3d9.h"

float Get_FPS(){
	static int nFrameCount = 0;
	static float FPS = 0.0f;
	static float currentTime = 0.0f;
	static float lastTime = 0.0f;

	++nFrameCount;
	currentTime = timeGetTime() * 0.001f;

	float dirtaTime = currentTime - lastTime;
	if (dirtaTime > 1.0f){
		FPS = nFrameCount / dirtaTime;
		lastTime = currentTime;
		nFrameCount = 0;
	}

	return FPS;
}