#include "DirectionalLight.h"
#include "../../Buffer/constantBuffer/DirectionalLightBuffer/DirectionalLightBuffer.h"
#include "../../../../commonVariables.h"

void DirectionalLight::Update()
{
	Vector3 color_ = color * CommonV::inv_255;
	dirLightBuffer->dirLight.buffMap->color = color_;
	dirLightBuffer->dirLight.buffMap->intensity = intensity;
	dirLightBuffer->dirLight.buffMap->pos = pos;

}

void DirectionalLight::Init()
{
	color = { 25,28,50};
	intensity = 1.0f;
	pos = { 1,1,1 };

}

void DirectionalLight::Reset()
{

}

DirectionalLight::DirectionalLight(DirectionalLightBuffer* dirLightBuffer_)
{
	dirLightBuffer = dirLightBuffer_;
}
