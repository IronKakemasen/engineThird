#include "../HLSLI/Material.hlsli"

Texture2D<float4> albedoTex : register(t1);
SamplerState gSampler : register(s0);
ConstantBuffer<Material> gMaterial : register(b0);

struct PixcelShaderOutput
{
    float4 color : SV_TARGET0;
};

struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : POSITOIN0;
};

PixcelShaderOutput main(VertexShaderOutput input)
{
    PixcelShaderOutput output;

    float4 transformedUV = mul(float4(input.texcoord.x, input.texcoord.y, 1.0f, 1.0f), gMaterial.uvTransform);
    float4 textureColor = albedoTex.Sample(gSampler, transformedUV.xy);

    output.color = gMaterial.albedoColor * textureColor;

    return output;

}



