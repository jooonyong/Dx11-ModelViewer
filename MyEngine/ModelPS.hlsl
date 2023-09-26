Texture2D shaderTexture;
SamplerState SampleType;

cbuffer LightBuffer
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 lightDirection;
	float specularPower;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
};

float4 main(PixelInputType input) : SV_TARGET 
{
	float4 textureColor = shaderTexture.Sample(SampleType, input.tex);
	
	float4 color = ambient;
	float4 specularColor = specular;
	
	float3 lightDir = -lightDirection;
	
	float lightIntensity = saturate(dot(input.normal, lightDir));

	if (lightIntensity > 0.0f)
	{
		color += (diffuse * lightIntensity);
		color = saturate(color);
		float3 reflection = normalize(2 * lightIntensity * input.normal - lightDir);
		specularColor = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
	}
	color = color * textureColor;
	
	return color;
}