#include "PointLight.h"
#include "../../Buffer/constantBuffer/PointLightBuffer/PointLightBuffer.h"
#include "../../../../commonVariables.h"
#include <math.h>

void PointLight::Update()
{
	Vector3 color_ = color * CommonV::inv_255;
	pLightBuffer->pLight.buffMap->intensity = intensity;
	pLightBuffer->pLight.buffMap->pos = pos;
	pLightBuffer->pLight.buffMap->radius = 1.0f / radius * radius;
}

void PointLight::Init()
{
	color = { 255,255,255 };
	intensity = 1.0f;
	pos = { 1,1,1 };

}

void PointLight::Reset()
{

}

PointLight::PointLight(PointLightBuffer* pLightBuffer_)
{
	pLightBuffer = pLightBuffer_;
	radius = 5.0f;
}
