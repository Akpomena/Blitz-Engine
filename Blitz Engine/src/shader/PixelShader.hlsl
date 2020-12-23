
cbuffer ConstBuffer
{
	float4 colors[6];
};

float4 main(uint uid: SV_PRIMITIVEID) : SV_TARGET
{
	return colors[uid / 2];
}