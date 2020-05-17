#include "ColoredTriangle.hlsli"

VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT OUT = (VS_OUTPUT) 0;

	OUT.Position = float4(IN.Position, 1.0f);
	OUT.Color = IN.Color;

	return OUT;
}