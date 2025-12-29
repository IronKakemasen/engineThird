struct PointLight
{
    float3 pos;
    float intensity;
    float3 color;
    float invSqrRadius; 
    int isActive;

};

float SmoothDistanceAttenuation(float sqrtDistance_, float invSqrtRadius_)
{
    float factor = sqrtDistance_ * invSqrtRadius_;
    float smoothFactor = saturate(1.0f - (factor * factor));
    return smoothFactor * smoothFactor;
}

float GetDistanceAttenuation(float3 unnormalizedToObject_,float invSqrtRadius_ )
{
    const float minDistance = 0.01f;
    
    float sqrDist = dot(unnormalizedToObject_, unnormalizedToObject_);
    float attenuation = 1.0f / max(sqrDist, minDistance * minDistance);

    attenuation *= SmoothDistanceAttenuation(sqrDist, invSqrtRadius_);

    return attenuation;
}

float3 EvaluatePointLight( float3 normal_ , float3 worldPos_, float3 lightPos_, 
    float invSqrtRadius_, float3 lightColor_ )
{
    float3 dif = lightPos_ - worldPos_;
    float3 L = normalize(dif);
    float att = GetDistanceAttenuation(dif, invSqrtRadius_);

    return saturate(dot(normal_, L)) * lightColor_ * att / (4.0f * 3.14159265359f);
}
