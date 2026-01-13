#include "../HLSLI/MaterialForLine.hlsli"
#include "../HLSLI/DirectionalLight.hlsli"
#include "../HLSLI/ComputeLight.hlsli"
#include "../HLSLI/CameraPara.hlsli"
#include "../HLSLI/PointLight.hlsli"

SamplerState baseColorSmp : register(s0);
SamplerState nomalSmp : register(s1);
SamplerState specularMap : register(s2);
SamplerState shininessMap : register(s3);

ConstantBuffer<MaterialForLine> gMaterial : register(b1);

struct VertexShaderOutput
{
    float4 position : SV_POSITION;
};


struct PixcelShaderOutput
{
	float4 color : SV_TARGET0;
};


PixcelShaderOutput main(VertexShaderOutput input)
{
    PixcelShaderOutput output;
    output.color = gMaterial.albedoColor;
    
    return output;
}

