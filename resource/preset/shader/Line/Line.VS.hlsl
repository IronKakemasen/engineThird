#include "../HLSLI/TransformMatrix.hlsli"
#include "../HLSLI/VertexShaderInput.hlsli"

struct VertexShaderOutput
{
    float4 position : SV_POSITION;
};

ConstantBuffer<WVPMatrix> viewProjectiton : register(b0);

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
    float4 tmp = float4(input.position.x, input.position.y, input.position.z,1.0f);
    output.position = mul(tmp, viewProjectiton.WVP);
    
	return output;
}



