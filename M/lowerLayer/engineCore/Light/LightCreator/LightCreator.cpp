#include "LightCreator.h"
#include "../../Render/ExclusiveDraw/ExclusiveDraw.h"

PointLight* LightCreator::CreatePointLight()
{
	static int createNum = 0;
	if (createNum > pLightCreationLimit) assert(false);

	pLightSet.first.reset(new PointLightBuffer);
	pLightSet.second.reset(new PointLight(pLightSet.first.get()));

	pLightSet.first->pLight.CreateAndMapping(device);

	exclusiveDraw->Setter_PointLightBuffer(pLightSet.first.get());
	createNum++;

	return pLightSet.second.get();
}


DirectionalLight* LightCreator::CreateDirectionalLight()
{
	static int createNum = 0;
	if (createNum > 0) assert(false);

	dirLightSet.first.reset(new DirectionalLightBuffer);
	dirLightSet.second.reset(new DirectionalLight(dirLightSet.first.get()));

	dirLightSet.first->dirLight.CreateAndMapping(device);

	exclusiveDraw->Setter_DirectionalLightBuffer(dirLightSet.first.get());
	createNum++;

	return dirLightSet.second.get();
}

void LightCreator::Init(ExclusiveDraw* exclusiveDraw_, ID3D12Device* device_)
{
	exclusiveDraw = exclusiveDraw_;
	device = device_;
}
