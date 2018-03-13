
float4 lightDirection; 
float4 materialAmbient : MATERIALAMBIENT;
float4 materialDiffuse : MATERIALDIFFUSE;
float fogNear;
float fogFar;
static const int MAX_MATRICES = 80;
float4x3 mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4 mViewProj : VIEWPROJECTION;

struct VS_INPUT{
	float4  pos          : POSITION;
	float4  blendWeights : BLENDWEIGHT;
	float4  blendIndices : BLENDINDICES;
	float3  normal       : NORMAL;
	float2  tex0         : TEXCOORD0;
};
	 
struct VS_OUTPUT{
	float4  pos     : POSITION;
	float4  diffuse : COLOR;
	float2  tex0    : TEXCOORD0;
	float   fog     : FOG;
};

float3 CalcDiffuse(float3 normal){
	float res;
	res = max(0.0f, dot(normal, lightDirection.xyz));   
	return (res);
}

VS_OUTPUT DefaultTransform(VS_INPUT i, uniform int numBones){
	VS_OUTPUT o;
	float3 pos = 0.0f;
	float3 normal = 0.0f;    
	float lastWeight = 0.0f;

	o.pos = mul(float4(pos.xyz, 1.0f), mViewProj);


	o.diffuse.xyz = 1;
	o.diffuse.w = materialAmbient.w * materialDiffuse.w;

	o.fog = 1;

	o.tex0 = i.tex0;
	
	
	
	return o;
}

technique BasicTec{
	pass P0{
		VertexShader = compile vs_2_0 DefaultTransform(4);
	}
}