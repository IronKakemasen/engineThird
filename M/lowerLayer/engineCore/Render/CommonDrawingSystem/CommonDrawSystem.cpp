#include "CommonDrawSystem.h"

CommonDrawingSystem::CommonDrawingSystem()
{
	color = { 255,255,255,255 };
	cullMode = kCullModeBack;
	blendMode = kBlendModeNormal;
	shaderSetIndex = 0;
	doDraw = true;
	id = -1;
	texHandle = 0;		//(White2x2)
}


