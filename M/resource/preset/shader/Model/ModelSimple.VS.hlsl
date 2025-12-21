#include "../HLSLI/TransformMatrix.hlsli"
#include "../HLSLI/VertexOutput.hlsli"


struct VertexShaderInput
{
    float3 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 tangent : TANGENT;

};

ConstantBuffer<WorldMatrix> gWorldMatrix : register(b0);
ConstantBuffer<WVPMatrix> gWVPMatrix : register(b1);
//ConstantBuffer<CameraParameters> gCameraParameters : register(b2);


VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    output.texcoord = input.texcoord;
    float4 tmp = float4(input.position.x, input.position.y, input.position.z, 1.0f);
    
    output.position = mul(tmp, gWVPMatrix.WVP);
    output.normal = normalize(mul(input.normal, (float3x3) gWorldMatrix.World));
    output.worldPosition = float3(gWorldMatrix.World[3][0], gWorldMatrix.World[3][1], gWorldMatrix.World[3][2]);
    
    return output;
}



