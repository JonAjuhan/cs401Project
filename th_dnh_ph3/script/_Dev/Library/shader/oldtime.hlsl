
//Color tint shader
// Tints the target priority with the specified colors
// if s_bw = 1, then the screen will become black and white
//		s_red is also used arbitrarily to manipulate the "intensity" of the black and white (from 0 to 1)


sampler sampler0_ : register(s0);

const float SCREEN_WIDTH = 1024;
const float SCREEN_HEIGHT = 512;
float s_red;
float s_green;
float s_blue;
float s_seed;
float s_noise_intensity;
float s_transfer;

struct PS_INPUT{
	float4 diffuse : COLOR0;
	float2 texCoord : TEXCOORD0;
	float2 vPos : VPOS;
};

struct PS_OUTPUT{
	float4 color : COLOR0;
};


float rand_1_05(in float2 uv){
    float2 noise = (frac(sin(dot(uv ,float2(12.9898,78.233)*2.0)) * 43758.5453));
    return abs(noise.x + noise.y) * 0.5;
}


PS_OUTPUT PsTask( PS_INPUT In ) : COLOR0{
	PS_OUTPUT Out;
	
	float4 colorTexture = tex2D(sampler0_, In.texCoord);
	float4 colorDiffuse = In.diffuse;
	float4 color = colorTexture * colorDiffuse;	
	
	float incol = ( color.r + color.g + color.b ) * 0.3333f;
	
	float si = s_noise_intensity;
	float st = s_transfer;
	
	float distm = In.texCoord.x + noise(In.vPos.x*In.vPos.y*0.2*s_seed);
	
	float noiseseed = sin(s_seed*rand_1_05(In.vPos));
	float noisemod = -si*abs(noiseseed*noiseseed*noiseseed*noiseseed*noiseseed);
	
	
	Out.color.r = color.r * (1-st) + st * (incol * s_red * (1+noisemod));
	Out.color.g = color.g * (1-st) + st * (incol * s_green * (1+noisemod));
	Out.color.b = color.b * (1-st) + st * (incol * s_blue * (1+noisemod));
	
	Out.color.a = color.a;

	return Out;
}


technique TecMain{
	pass P0{
		PixelShader = compile ps_3_0 PsTask();
	}
}