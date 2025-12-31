#include "LightBehavior.h"

PointLightPara::PointLightPara()
{
	isActive = 0;
	invSqrRadius = 5.0f;
	color = { 255,255,255 };
	intensity = 100.0f;
	pos = { 0.1f,2.4f,2.2f };

}

LightBasePara::LightBasePara()
{
	isActive = 0;

}
