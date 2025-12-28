#include "../HLSLI/Material.hlsli"

Texture2D<float4> albedoTex : register(t0);
SamplerState baseColorSmp : register(s0);
SamplerState nomalSmp : register(s1);
SamplerState metalicMap : register(s2);
SamplerState roughnessMap : register(s3);

//コンスタントバッファの定義
//b = constantBuffer,0 = shader上でのresourceナンバー
ConstantBuffer<Material>gMaterial : register(b2);
//ConstantBuffer<DirectionalLight> gDirectionalLight : register(b3);

struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : POSITOIN0;
};


struct PixcelShaderOutput
{
	float4 color : SV_TARGET0;
};


PixcelShaderOutput main(VertexShaderOutput input)
{
    PixcelShaderOutput output;


    float4 transformedUV = mul(float4(input.texcoord.x, input.texcoord.y, 1.0f, 1.0f), gMaterial.uvTransform);
    float4 textureColor = albedoTex.Sample(baseColorSmp, transformedUV.xy);
    
    output.color = gMaterial.albedoColor * textureColor;

   //output.color = gMaterial.color;

    return output;

}

