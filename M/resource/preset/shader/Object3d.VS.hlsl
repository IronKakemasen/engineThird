#include "dousite.hlsli"


struct WorldMatrix
{
    float4x4 World;

};

struct VertexShaderInput
{
	float3 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

ConstantBuffer<WorldMatrix> gWorldMatrix : register(b0);
ConstantBuffer<CameraParameters> gCameraParameters : register(b1);


VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	output.texcoord = input.texcoord;
    float4 tmp = float4(input.position.x, input.position.y, input.position.z,1.0f);
    
    output.position = mul(tmp, mul(gWorldMatrix.World, gCameraParameters.viewProjection));
    output.normal = normalize(mul(input.normal, (float3x3) gWorldMatrix.World));
    output.worldPosition = mul(tmp, gWorldMatrix.World).xyz;
    
	return output;
}



