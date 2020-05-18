#include "TexturedCube.hlsli"

float4 main(VS_OUTPUT IN) : SV_TARGET
{
	return IN.Color;
}