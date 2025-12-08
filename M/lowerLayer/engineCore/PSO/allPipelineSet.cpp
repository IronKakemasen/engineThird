#include "allPipelineSet.h"
#include "../../../utilities/benriTemplateFunc/benriTempFunc.h"
#include <assert.h>
#include "../VpShader/vpShaders.h"


void AllPipelineSet::Initialize(ID3D12Device* device_, VpShaders* vpShaders_, ID3D12GraphicsCommandList* commandList_)
{
	commandList = commandList_;
	vpShaders = vpShaders_;
	device = device_;

}

void AllPipelineSet::CreateNewPipeline(
	std::string folderPath_,
	std::string vsFileName_,
	std::string psFileName_,
	std::function<std::vector<D3D12_INPUT_ELEMENT_DESC>()> inputElementDescCreateFunc_,
	std::function<std::vector<D3D12_ROOT_PARAMETER>()> rootParameterCreateFunc_)
{
	std::string tableName = vsFileName_ + " + " + psFileName_;

	vpShaders->AddPixelShader(folderPath_,psFileName_);
	vpShaders->AddVertexShader(folderPath_,vsFileName_);
	vpShaders->AddToTable(tableName, psFileName_, vsFileName_);
	pipelineSets[0][0][0]->Activate_InputLayoutCreateFunc(inputElementDescCreateFunc_);
	pipelineSets[0][0][0]->Activate_RootparameterCreateFunc(rootParameterCreateFunc_);

	Add(tableName);

}

void AllPipelineSet::Add(std::string shaderSetName_, bool isTopologyLine)
{
	if (vpShaders)
	{
		auto* vpShaderTable = vpShaders->Getter_VPShaderTable();

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

		//CommandListSetter
		for (int k = 0; k < kCountOfBlendMode; ++k)
		{
			for (int j = 0; j < kCountOfCullMode; ++j)
			{
				pipelineSets[shaderSetIndex][k][j]->Setter_Commandlist(commandList);
			}
		}
	}

	else
	{
		assert(false);
	}
}

