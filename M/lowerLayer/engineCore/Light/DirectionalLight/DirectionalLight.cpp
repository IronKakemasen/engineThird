#include "DirectionalLight.h"
#include "../../Buffer/constantBuffer/DirectionalLightBuffer/DirectionalLightBuffer.h"
#include "../../../../commonVariables.h"
#include "../../../../utilities/benriTemplateFunc/benriTempFunc.h"
void DirectionalLight::Update()
{

}

void DirectionalLight::Init()
{
	para.color = { 100,100,100 };
	para.intensity = 2.0f;
	para.pos = { 1,14,-1.7f };
	para.isActive = 1;
}

void DirectionalLight::Reset()
{

}

DirectionalLight::DirectionalLight()
{

}
