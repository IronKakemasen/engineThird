
float3 Diffuse(float3 normal_ , float3 lightDir_, float3 diffuse_,
    float3 lightColor_,float intensity_)
{
    float cos = saturate(dot(normal_, lightDir_));
    
    return lightColor_ * cos * diffuse_ * intensity_;
}

float3 Specular(float3 normal_, float3 lightDir_, float3 toCamera_, float3 specular_,
    float3 lightColor_ , float intensity_ , float shininess_)
{
    float3 reflection = normalize(-reflect(toCamera_, normal_));
    return lightColor_ * specular_ * pow(saturate(dot(lightDir_, reflection)), shininess_) * 
        intensity_;
    
}