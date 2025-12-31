#include "DirectionalLight.h"
#include "../../Buffer/constantBuffer/DirectionalLightBuffer/DirectionalLightBuffer.h"
#include "../../../../commonVariables.h"
#include "../../../../utilities/benriTemplateFunc/benriTempFunc.h"
void DirectionalLight::Update()
{

}

void DirectionalLight::Init()
{
	para.color = { 25,28,50};
	para.intensity = 1.0f;
	para.pos = { 1,1,1 };

}

void DirectionalLight::Reset()
{

}

DirectionalLight::DirectionalLight()
{

}
