
cbuffer VS_CONSTANT_BUFFER : register(b0)
{
	matrix transform;
};

struct INPUT_DATA
{
	float3 Position: POSITION;
	float2 TexCoord: TEXCOORD;
};

struct OUTPUT_DATA
{
	float2 TexCoord: TEXCOORD;
	float4 FinalPosition : SV_POSITION;
};

OUTPUT_DATA main(INPUT_DATA input)
{
	OUTPUT_DATA Data;
	Data.TexCoord = input.TexCoord;
	Data.FinalPosition = mul(float4(input.Position, 1.0f), transform);
	return  Data;
}