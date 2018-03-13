
//Simple masking shader:
//Takes pixels from the destination layer and uses the alpha to determine to show the shader's source image


sampler sampler0_ : register(s0);

const float SCREEN_WIDTH = 1024;
const float SCREEN_HEIGHT = 512;
float p_int;
float p_frame;

texture textureMask_;
sampler samplerMask_ = sampler_state{ 
	Texture = <textureMask_>;
};



struct PS_INPUT{
	float4 diffuse : COLOR0;
	float2 texCoord : TEXCOORD0;
	float2 vPos : VPOS;
};


struct PS_OUTPUT{
	float4 color : COLOR0;
};

PS_OUTPUT PsMask( PS_INPUT In ) : COLOR0{
	PS_OUTPUT Out;
	
	float4 colorTexture = tex2D(sampler0_, In.texCoord);
	float4 colorDiffuse = In.diffuse;
	float4 color = colorTexture * colorDiffuse;	
	
	float nang2 = radians(In.vPos.y*3+p_frame);
	float nang = sin(nang2);
	
	float2 maskUV;
	In.vPos.x = In.vPos.x;
	In.vPos.y = In.vPos.y;
	maskUV.x = In.vPos.x / (SCREEN_WIDTH) * (1+p_int) + p_int*nang;
	maskUV.y = In.vPos.y / (SCREEN_HEIGHT) * (1+p_int) + p_int*nang/2;
	float4 colorMask = tex2D(samplerMask_, maskUV);
	
	Out.color.rgb = ( colorMask.r + colorMask.g + colorMask.b ) * 0.3333f;
	//Out.color.a = ((( color.r + color.g + color.b ) * 0.3333f) * color.a);
	Out.color.a = color.a;

	return Out;
}



technique TecMask{
	pass P0{
		PixelShader = compile ps_3_0 PsMask();
	}
}