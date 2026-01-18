#include "../HLSLI/Material.hlsli"
#include "../HLSLI/DirectionalLight.hlsli"
#include "../HLSLI/ComputeLight.hlsli"
#include "../HLSLI/CameraPara.hlsli"
#include "../HLSLI/PointLight.hlsli"


Texture2D<float4> colorMap : register(t0);
StructuredBuffer<PointLight> pointLights : register(t1);

SamplerState baseColorSmp : register(s0);
SamplerState nomalSmp : register(s1);
SamplerState specularMap : register(s2);
SamplerState shininessMap : register(s3);

ConstantBuffer< Material > gMaterial : register(b1);
ConstantBuffer< DirectionalLight > dirLight : register(b2);
ConstantBuffer< CameraPara > cameraPara : register(b3);

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
    float4 textureColor = colorMap.Sample(baseColorSmp, transformedUV.xy);
    float4 baseColor = textureColor * gMaterial.albedoColor;

    float3 normal = normalize(input.normal);
    float3 toCamera = normalize(cameraPara.cameraPos - input.worldPosition);

    float NV = saturate(dot(normal, toCamera));
    float3 diffuse = DiffuseModelNormalizedLambert(baseColor.rgb, gMaterial.metallic);
    float3 Ks = baseColor.rgb * gMaterial.metallic;
    float a = gMaterial.roughness * gMaterial.roughness;

    float3 lightFinalColor = float3(0, 0, 0);
    
    //直接光
    float3 dirLightDir = normalize(dirLight.pos);
    float3 dirColor = dirLight.color * dirLight.intensity * dirLight.isActive;

    float3 dirLightBRDF = ComputeBRDF(diffuse, dirLightDir, toCamera, normal, NV, Ks, a);
    lightFinalColor += dirColor * dirLightBRDF;

    //ポイントライト
    uint numLights, stride;
    pointLights.GetDimensions(numLights, stride);
    
    for (uint i = 0; i < numLights; ++i)
    {
        if (!pointLights[i].isActive) continue;

        float3 pointLightDir = normalize(pointLights[i].pos - input.worldPosition);

        float3 poinghtLightColor = EvaluatePointLight(normal, input.worldPosition, 
            pointLights[i].pos, pointLights[i].invSqrRadius,
            pointLights[i].color) * pointLights[i].intensity * pointLights[i].isActive;
        
        float3 pointLightBRDF = ComputeBRDF(diffuse, pointLightDir, toCamera, normal, NV, Ks, a);
        lightFinalColor += poinghtLightColor * pointLightBRDF;
    }
    
    output.color = float4(lightFinalColor, baseColor.a);
    
    return output;
}

