#include "ColoredCube.hlsli"

cbuffer ConstantBuffer
{
	float4x4 WorldViewProjectionMatrix;
};

VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT OUT = (VS_OUTPUT) 0;
	
	OUT.Position = mul(WorldViewProjectionMatrix, float4(IN.Position, 1.0));

	OUT.Color = IN.Color;

	return OUT;
}