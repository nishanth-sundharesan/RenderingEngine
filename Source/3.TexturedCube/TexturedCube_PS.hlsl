#include "TexturedCube.hlsli"

Texture2D CubeTexture : register(t0);
SamplerState BilinearSampler : register(s0);

float4 main(VS_OUTPUT IN) : SV_TARGET
{
	return CubeTexture.Sample(BilinearSampler, IN.UV.xy);
}