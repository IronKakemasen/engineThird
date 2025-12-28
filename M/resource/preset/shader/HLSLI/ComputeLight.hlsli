
static const float kPi = 3.14159265359f;
static const float kInv_pi = 1.0f / 3.14159265359f;


float3 DiffuseModelNormalizedLambert(float3 baseColor_, float metalic_)
{
    return baseColor_ * (1.0f - metalic_) * kInv_pi;
}

float3 DiffuseModelLambert(float3 normal_ , float3 lightDir_, float3 diffuse_,
    float3 lightColor_,float intensity_)
{
    float cos = saturate(dot(normal_, lightDir_));
    
    return lightColor_ * cos * diffuse_ * intensity_;
}

float3 SpecularModelPhong(float3 normal_, float3 lightDir_, float3 toCamera_, float3 specular_,
    float3 lightColor_ , float intensity_ , float shininess_)
{
    float3 reflection = normalize(-reflect(toCamera_, normal_));
    return lightColor_ * specular_ * pow(saturate(dot(lightDir_, reflection)), shininess_) * 
        intensity_;   
}

float3 SpecularModelNormalizedPhong(float3 baseColor_ , float metalic_,
    float shininess_, float3 lightDir_, float3 normal_, float3 toCamera_)
{
    float3 reflection = normalize(-toCamera_ + 2.0f * dot(normal_, toCamera_) * normal_);
    float LR = saturate(dot(lightDir_, reflection));
    
    return baseColor_ * metalic_ * ((shininess_ + 2.0f) / (2.0f * kPi)) * pow(LR, shininess_);
}

float3 SchlickFrensnel(float3 normal_, float3 lightDir_,float3 toCamera_ , float3 specularColor_)
{
    float3 H = normalize(toCamera_ + lightDir_);
    float VH = saturate(dot(toCamera_, H));
    return specularColor_ + (1.0f - specularColor_) * pow((1.0f - VH), 5.0f);
}


float Distribution_Beckmann(float m, float NH)
{
    float c2 = NH * NH;
    float c4 = c2 * c2;
    float m2 = m * m;

    return (1.0f / (m2 * c4)) * exp((-1.0f / m2) * (1.0f - c2) / c2);
}

float ShadowMasking_Vcavity(float NH, float NV, float NL, float VH)
{
    return min(1.0f, min(2.0f * NH * NV / VH, 2.0f * NH * NL / VH));
}

