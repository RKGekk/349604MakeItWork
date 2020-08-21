Texture2D shaderTexture;

SamplerState SampleType;

struct PixelInputType {
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD;
};

float4 TexturePixelShader(PixelInputType input) : SV_TARGET {

    float4 textureColor;

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, input.tex);
    //textureColor = shaderTexture.Sample(SampleType, float2(frac(input.tex.x), frac(input.tex.y)));
    
    return textureColor;
}