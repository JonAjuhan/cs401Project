
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
float s_bw;

struct PS_INPUT{
	float4 diffuse : COLOR0;
	float2 texCoord : TEXCOORD0;
	float2 vPos : VPOS;
};

struct PS_OUTPUT{
	float4 color : COLOR0;
};

PS_OUTPUT PsTask( PS_INPUT In ) : COLOR0{
	PS_OUTPUT Out;
	
	float4 colorTexture = tex2D(sampler0_, In.texCoord);
	float4 colorDiffuse = In.diffuse;
	float4 color = colorTexture * colorDiffuse;	
	
	Out.color.r = color.r * s_red;
	Out.color.g = color.g * s_green;
	Out.color.b = color.b * s_blue;
	
	if(s_bw == 1){
		float incol = ( color.r + color.g + color.b ) * 0.3333f;
		float modif = s_red;
		Out.color.r = incol * modif + color.r * (1-modif);
		Out.color.g = incol * modif + color.g * (1-modif);
		Out.color.b = incol * modif + color.b * (1-modif);
	}
	
	Out.color.a = color.a;

	return Out;
}



technique TecColor{
	pass P0{
		PixelShader = compile ps_3_0 PsTask();
	}
}