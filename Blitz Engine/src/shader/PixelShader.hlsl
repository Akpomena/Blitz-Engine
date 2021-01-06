
cbuffer ConstBuffer
{
	float4 colors[6];
};

struct INPUT_DATA
{
	float2 TexCoord: TEXCOORD;
};

SamplerState samp;
texture2D tex;

float4 main(INPUT_DATA input) : SV_TARGET
{
	return tex.Sample(samp, input.TexCoord);
}