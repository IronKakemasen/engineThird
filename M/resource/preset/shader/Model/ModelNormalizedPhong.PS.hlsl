#include "../HLSLI/Material.hlsli"
#include "../HLSLI/DirectionalLight.hlsli"
#include "../HLSLI/ComputeLight.hlsli"
#include "../HLSLI/CameraPara.hlsli"

Texture2D<float4> colorMap : register(t0);

SamplerState gSampler : register(s0);

ConstantBuffer<Material> gMaterial : register(b1);
ConstantBuffer<DirectionalLight> dirLight : register(b2);
ConstantBuffer<CameraPara> cameraPara : register(b3);


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
    float4 textureColor = colorMap.Sample(gSampler, transformedUV.xy);

    float3 dirLightDir = normalize(dirLight.pos);
    float3 normal = normalize(input.normal);
    float3 toCamera = normalize(cameraPara.cameraPos - input.worldPosition);
    float NL = saturate(dot(normal, dirLightDir));
    
    float3 diffuse = DiffuseModelNormalizedLambert(gMaterial.albedoColor.rgb, gMaterial.metallic);
    float3 specular =
    SpecularModelNormalizedPhong(gMaterial.albedoColor.rgb, gMaterial.metallic,
    gMaterial.shininess, dirLightDir, normal, toCamera);
    
    specular = SchlickFrensnel(normal, dirLightDir, toCamera, specular);

    output.color = float4(dirLight.color * dirLight.intensity* textureColor.rgb *
        (diffuse + specular) * NL, gMaterial.albedoColor.a * textureColor.a);
    
    return output;

}

