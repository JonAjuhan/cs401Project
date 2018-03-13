

sampler sampler0_ : register(s0);

float p_int;
float p_frame;

struct PS_INPUT{
	float4 diffuse : COLOR0;
	float2 texCoord : TEXCOORD0;
	float2 vPos : VPOS; 
};


struct PS_OUTPUT {
    float4 color : COLOR0;
};


PS_OUTPUT PsTask( PS_INPUT In ) : COLOR0{
	PS_OUTPUT Out;

	float nang2 = radians(In.vPos.y*3+p_frame);
	float nang = sin(nang2);
	
	float2 texUV;
	texUV.x = In.texCoord.x + p_int*nang;
	texUV.y = In.texCoord.y;

	float4 colorTexture = tex2D(sampler0_, texUV);
	float4 colorDiffuse = In.diffuse;
	float4 color = colorTexture * colorDiffuse;
	Out.color = color;

	return Out;
}


technique TecMain{
	pass P0{
		PixelShader = compile ps_3_0 PsTask();
	}
}

