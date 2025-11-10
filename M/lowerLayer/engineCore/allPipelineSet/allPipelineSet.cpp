#include "allPipelineSet.h"
#include "../../../utilities/benriTemplateFunc/benriTempFunc.h"
#include <assert.h>


void AllPipelineSet::Initialize(ID3D12Device* device_, VPShaderTable* vpShaderTable_)
{
	vpShaderTable = vpShaderTable_;
	device = device_;

}

void AllPipelineSet::Add(std::string shaderSetName_, bool isTopologyLine)
{
	if (vpShaderTable)
	{
		assert(DoesContain(vpShaderTable->Getter_NameList(), shaderSetName_));

		int const shaderSetIndex = vpShaderTable->Getter_Map_nameAndID()[shaderSetName_];

		pipelineSets[shaderSetIndex][kBlendModeNormal][kCullModeBack] =
			PipelineSet::CreateGraphicsPipelineSet(device, shaderSetName_, vpShaderTable,
				kBlendModeNormal, CullMode::kCullModeBack, isTopologyLine);

		pipelineSets[shaderSetIndex][kBlendModeNormal][kCullModeFront] =
			PipelineSet::CreateGraphicsPipelineSet(device, shaderSetName_, vpShaderTable,
				kBlendModeNormal, CullMode::kCullModeFront, isTopologyLine);

		pipelineSets[shaderSetIndex][kBlendModeNormal][kCullModeNone] =
			PipelineSet::CreateGraphicsPipelineSet(device, shaderSetName_, vpShaderTable,
				kBlendModeNormal, CullMode::kCullModeNone, isTopologyLine);


		pipelineSets[shaderSetIndex][kBlendModeAdd][kCullModeBack] =
			PipelineSet::CreateGraphicsPipelineSet(device, shaderSetName_, vpShaderTable,
				kBlendModeNormal, CullMode::kCullModeBack, isTopologyLine);

		pipelineSets[shaderSetIndex][kBlendModeAdd][kCullModeFront] =
			PipelineSet::CreateGraphicsPipelineSet(device, shaderSetName_, vpShaderTable,
				kBlendModeNormal, CullMode::kCullModeFront, isTopologyLine);

		pipelineSets[shaderSetIndex][kBlendModeAdd][kCullModeNone] =
			PipelineSet::CreateGraphicsPipelineSet(device, shaderSetName_, vpShaderTable,
				kBlendModeNormal, CullMode::kCullModeNone, isTopologyLine);



	}

	else
	{
		assert(false);
	}
}

void AllPipelineSet::CreateAllGraphicsPipelineSets(ID3D12Device* device_, VPShaderTable* vpShaderTable_)
{


}
