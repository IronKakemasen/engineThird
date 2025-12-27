#include "Appearance.h"

Appearance::Appearance()
{
	color = { 255,255,255,255 };
	cullMode = kCullModeBack;
	blendMode = kBlendModeNormal;
	shaderSetIndex = 0;
	doDraw = true;
	texHandles[0] = 0;		//(White2x2)
}


