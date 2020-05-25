#include "TexturedCube.hlsli"

cbuffer ConstantBuffer : register(b0)
{
	float4x4 WorldViewProjectionMatrix;
};

VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT OUT = (VS_OUTPUT) 0;
	
	OUT.Position = mul(WorldViewProjectionMatrix, float4(IN.Position, 1.0));

	OUT.UV = IN.UV;

	return OUT;
}