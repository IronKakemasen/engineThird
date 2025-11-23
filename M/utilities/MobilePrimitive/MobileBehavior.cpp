#include "MobileBehavior.h"

MobileBehavior::MobileBehavior()
{
	color = { 255,255,255,255 };
	cullMode = kCullModeBack;
	drawMode = DrawMode::kSolid;
	blendMode = kBlendModeNormal;
	texHandle = M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2);

}