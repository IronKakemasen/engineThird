#include "PostEffects.h"
#include "../engineCore/textureDataManager/textureDataManager.h"
#include "../../M.h"
#include "../../../commonVariables.h"

PostEffects::Bloom::Bloom(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreen(textureDataManager_, numRequired_) {
}

void PostEffects::Bloom::Update()
{

}

void PostEffects::Bloom::Init(ID3D12Device* device_)
{

}


PostEffects::NoEffection::NoEffection(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreen(textureDataManager_, numRequired_) {
}

void PostEffects::NoEffection::Update()
{

}

void PostEffects::NoEffection::Init(ID3D12Device* device_)
{
	
	shaderSetIndex = M::GetInstance()->
		GetShaderSetIndexFromFileName("NoEffection.VS", "NoEffection.PS");
}

PostEffects::GreyScale::GreyScale(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreen(textureDataManager_, numRequired_) {
}

void PostEffects::GreyScale::Update()
{

}

void PostEffects::GreyScale::Init(ID3D12Device* device_)
{
	shaderSetIndex = M::GetInstance()->
		GetShaderSetIndexFromFileName("MonoChrome.VS", "MonoChrome.PS");

}

void PostEffects::SimpleNeonLike::Update()
{
	cBuffer.buffer.buffMap->backgroundDim = para.backgroundDim;
	cBuffer.buffer.buffMap->edgeWidth = para.edgeWidth;
	cBuffer.buffer.buffMap->texelSize = para.texelSize;

}

void PostEffects::SimpleNeonLike::Init(ID3D12Device* device_)
{
	shaderSetIndex = M::GetInstance()->
		GetShaderSetIndexFromFileName("SimpleNeonLike.VS", "SimpleNeonLike.PS");

	cBuffer.buffer.CreateAndMapping(device_);
	cBufferAddressContainer.emplace_back(cBuffer.buffer.GetVirtualGPUAddress());

	cBuffer.buffer.buffMap->backgroundDim = para.backgroundDim;
	cBuffer.buffer.buffMap->edgeWidth = para.edgeWidth;
	cBuffer.buffer.buffMap->texelSize = para.texelSize;

}

PostEffects::SimpleNeonLike::SimpleNeonLike(TextureDataManager* textureDataManager_, int numRequired_) :
	OffScreen(textureDataManager_, numRequired_) 
{
	para.backgroundDim = 0.01f;
	para.edgeWidth = 1.0f;
	//para.texelSize = { 1.0f / CommonV::kWindow_W,1.0f / CommonV::kWindow_H };
	para.texelSize = { 0.002f,0.002f };


}
