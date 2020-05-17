struct VS_INPUT
{
	float3 Position : POSITION;
	float4 Color : COLOR;
};

struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float4 Color	: COLOR;
};