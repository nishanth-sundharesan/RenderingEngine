struct VS_INPUT
{
	float3 Position : POSITION;
	float2 UV		: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float2 UV		: TEXCOORD;
};