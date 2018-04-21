
//Rainbow color modifying shader
// TecRainbow
// Will transform pixels in a rainbow wave
// s_period - How long the period of each wave is
// s_angle - The angle of the wave (you must edit this each iteration)
// s_horiz - the horizontal intensity (recommend have one of the set to 0)
// s_verti - the vertical intensity

sampler sampler0_ : register(s0);

const float SCREEN_WIDTH = 1024;
const float SCREEN_HEIGHT = 512;
float s_period;
float s_angle;
float s_horiz;
float s_verti;


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
	

	
	float insaturation = ( color.r + color.g + color.b ) * 0.3333f;
	
	float r_output_a = radians(s_period*(s_angle+In.vPos.x*s_horiz+In.vPos.y*s_verti));
	float r_output = 0.5+(sin(r_output_a+color.r*4))/2;
	Out.color.r = r_output;
	
	float g_output_a = radians(120+s_period*(s_angle+In.vPos.x*s_horiz+In.vPos.y*s_verti));
	float g_output = 0.5+(sin(g_output_a+color.g*4))/2;
	Out.color.g = g_output;
	
	float b_output_a = radians(240+s_period*(s_angle+In.vPos.x*s_horiz+In.vPos.y*s_verti));
	float b_output = 0.5+(sin(b_output_a+color.b*4))/2;
	Out.color.b = b_output;
	
	Out.color.a = color.a;

	return Out;
}


technique TecRainbow{
	pass P0{
		PixelShader = compile ps_3_0 PsTask();
	}
}