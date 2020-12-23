
cbuffer VS_CONSTANT_BUFFER : register(b0)
{
	matrix transform;
};

float4 main( float3 pos : POSITION ) : SV_POSITION
{
	return  mul(float4(pos, 1.0f), transform);
}