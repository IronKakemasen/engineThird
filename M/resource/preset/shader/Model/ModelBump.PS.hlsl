#include "../HLSLI/Material.hlsli"
#include "../HLSLI/VertexOutput.hlsli"
#include "../HLSLI/DirectionalLight.hlsli"
#include "../HLSLI/ComputeLight.hlsli"
#include "../HLSLI/CameraPara.hlsli"

Texture2D<float4> colorMap : register(t0);
Texture2D<float4> normalMap : register(t1);

SamplerState gSampler : register(s0);

ConstantBuffer<Material> gMaterial : register(b1);
ConstantBuffer<DirectionalLight> dirLight : register(b2);
ConstantBuffer<CameraPara> cameraPara : register(b3);


struct PixcelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixcelShaderOutput main(VertexShaderOutput input)
{
    PixcelShaderOutput output;

    float4 transformedUV = mul(float4(input.texcoord.x, input.texcoord.y, 1.0f, 1.0f), gMaterial.uvTransform);
    float4 textureColor = colorMap.Sample(gSampler, transformedUV.xy);
    float3 color = gMaterial.albedoColor.rgb * textureColor.rgb;

    float3 dirLightDir = normalize(float3(dirLight.pos.x, dirLight.pos.y, dirLight.pos.z));
    float3 normal = normalize(input.normal);
    float3 toCamera = normalize(cameraPara.cameraPos - input.worldPosition);
    
    float3 diffuse = Diffuse(normal, dirLightDir, gMaterial.diffuse, dirLight.color, dirLight.intensity);
    float3 specular = Specular(normal, dirLightDir, toCamera, gMaterial.specular,
    dirLight.color, dirLight.intensity, gMaterial.shininess);
    
    output.color = float4(color.rgb * (diffuse + specular), gMaterial.albedoColor.a * textureColor.a);
    return output;

}

