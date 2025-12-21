#include "../HLSLI/Material.hlsli"
#include "../HLSLI/VertexOutput.hlsli"

Texture2D<float4> albedoTex : register(t0);
SamplerState gSampler : register(s0);

ConstantBuffer<Material> gMaterial : register(b1);


struct PixcelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixcelShaderOutput main(VertexShaderOutput input)
{
    PixcelShaderOutput output;


    float4 transformedUV = mul(float4(input.texcoord.x, input.texcoord.y, 1.0f, 1.0f), gMaterial.uvTransform);
    float4 textureColor = albedoTex.Sample(gSampler, transformedUV.xy);
    
    output.color = gMaterial.albedoColor * textureColor;

    return output;

}

