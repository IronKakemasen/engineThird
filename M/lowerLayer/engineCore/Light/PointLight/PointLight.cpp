#include "PointLight.h"
#include "../../Buffer/constantBuffer/PointLightBuffer/PointLightBuffer.h"
#include "../../../../commonVariables.h"

#include <math.h>

void PointLight::Update()
{
	Vector3 color_ = color * CommonV::inv_255;
	pLightBuffer->pLight.buffMap->color = color_;
	pLightBuffer->pLight.buffMap->intensity = intensity;
	pLightBuffer->pLight.buffMap->pos = pos;
	pLightBuffer->pLight.buffMap->invSqrRadius = 1.0f / (invSqrRadius * invSqrRadius);
	pLightBuffer->pLight.buffMap->isActive = isActive;

}

void PointLight::Init()
{
	color = { 255,255,255 };
	intensity = 100.0f;
	pos = { 0.1f,2.4f,2.2f };

}

void PointLight::Reset()
{

}

PointLight::PointLight(PointLightBuffer* pLightBuffer_)
{
	pLightBuffer = pLightBuffer_;
	invSqrRadius = 5.0f;
	isActive = false;
}
