#include "../HLSLI/Material.hlsli"
#include "../HLSLI/DirectionalLight.hlsli"
#include "../HLSLI/ComputeLight.hlsli"
#include "../HLSLI/CameraPara.hlsli"
#include "../HLSLI/PointLight.hlsli"


Texture2D<float4> colorMap : register(t0);

SamplerState baseColorSmp : register(s0);
SamplerState nomalSmp : register(s1);
SamplerState specularMap : register(s2);
SamplerState shininessMap : register(s3);

ConstantBuffer<Material> gMaterial : register(b2);
ConstantBuffer<DirectionalLight> dirLight : register(b3);
ConstantBuffer<CameraPara> cameraPara : register(b4);
ConstantBuffer<PointLight> pLight : register(b5);

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
    float4 textureColor = colorMap.Sample(baseColorSmp, transformedUV.xy);

    float3 dirLightDir = normalize(dirLight.pos);
    float3 pointLightDir = normalize(pLight.pos - input.worldPosition);

    float3 normal = normalize(input.normal);
    float3 toCamera = normalize(cameraPara.cameraPos - input.worldPosition);

    float NV = saturate(dot(normal, toCamera));
    float3 diffuse = DiffuseModelNormalizedLambert(gMaterial.albedoColor.rgb, gMaterial.metallic);
    float3 Ks = gMaterial.albedoColor.rgb * gMaterial.metallic;
    float a = gMaterial.roughness * gMaterial.roughness;

    float3 poinghtLightColor = EvaluatePointLight(normal, input.worldPosition,
    pLight.pos, pLight.invSqrRadius, pLight.color) * pLight.intensity;
    float3 pointLightBRDF = ComputeBRDF(diffuse, pointLightDir, toCamera, normal, NV, Ks, a);
    poinghtLightColor = poinghtLightColor * pointLightBRDF;
    
    float3 dirColor = dirLight.color * dirLight.intensity;
    float3 dirLightBRDF = ComputeBRDF(diffuse, dirLightDir, toCamera, normal, NV, Ks, a);
    dirColor = dirColor * dirLightBRDF;

    float3 lightColor = dirColor + poinghtLightColor;
    
    //output.color = float4(lightColor * textureColor.rgb ,
    //    gMaterial.albedoColor.a * textureColor.a);
    
    output.color = float4(textureColor.rgb,
        gMaterial.albedoColor.a * textureColor.a);

    
    return output;
}

