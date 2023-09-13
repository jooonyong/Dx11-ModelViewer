Texture2D shaderTextures[3];
SamplerState SampleType;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 bodyColor;
	float4 faceColor;
	float4 hairColor;
	float4 color;

	bodyColor = shaderTextures[0].Sample(SampleType, input.tex);
	faceColor = shaderTextures[1].Sample(SampleType, input.tex);
	hairColor = shaderTextures[2].Sample(SampleType, input.tex);

	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}