#include "LightCreator.h"
#include "../../Render/ExclusiveDraw/ExclusiveDraw.h"

DirectionalLight* LightCreator::CreateDirecctoinalLight()
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
