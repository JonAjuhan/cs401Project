//from SamplePS03_HLSL

//================================================================
//大域設定値
//Texture
sampler sampler0_ : register(s0);

//--------------------------------
//ゆがみ生成用パラメータ
static const float RENDER_WIDTH = 1024; //レンダリングテクスチャの幅
static const float RENDER_HEIGHT = 1024; //レンダリングテクスチャの高さ

float frame_; //フレーム数
float enemyX_; //敵の位置X
float enemyY_; //敵の位置Y
float waveRadius_; //エフェクトの半径

float filterR;
float filterG;
float filterB;


//================================================================
//--------------------------------
//ピクセルシェーダ入力値
struct PS_INPUT
{
	float4 diffuse : COLOR0;  //ディフューズ色
	float2 texCoord : TEXCOORD0; //テクスチャ座標
	float2 vPos : VPOS; //描画先座標
};

//--------------------------------
//ピクセルシェーダ出力値
struct PS_OUTPUT
{
    float4 color : COLOR0; //出力色
};


//================================================================
// シェーダ
//--------------------------------
//ピクセルシェーダ
PS_OUTPUT PsWave( PS_INPUT In ) : COLOR0
{
	PS_OUTPUT Out;

	//--------------------------------
	//ゆらぎを計算
	float dist2 = pow(In.vPos.x-enemyX_ ,2) + pow(In.vPos.y-enemyY_ ,2);
	float dist = sqrt(dist2);
	float sinTheta = (In.vPos.y - enemyY_) / dist;
	float cosTheta = (In.vPos.x - enemyX_) / dist;

	//歪み作成用のsinに使用する角度パラメータ
	float angle = In.vPos.y - enemyY_ + In.vPos.x - enemyX_ + frame_;
	angle = radians(angle);

	//該当ピクセルの歪みの半径を計算
	//エフェクト半径の1/16を最大の歪み幅とする
	float waveRadius = waveRadius_ + waveRadius_/16 * (-1 + sin(angle));

	//中心から距離が離れるほど影響を小さくする
	float powerRatio = (waveRadius - dist) / waveRadius;
	if(powerRatio < 0){powerRatio = 0;}

	//色情報を取得する位置のバイアス値
	float biasRadius = waveRadius * powerRatio;
	float biasX = biasRadius * cosTheta;
	float biasY = biasRadius * sinTheta;

	//テクスチャの色情報を取得する位置
	float2 texUV;
	texUV.x = -biasX / RENDER_WIDTH + In.texCoord.x;
	texUV.y = -biasY / RENDER_HEIGHT + In.texCoord.y;


	//--------------------------------
	//テクスチャの色
	float4 colorTexture = tex2D(sampler0_, texUV);

	//頂点ディフーズ色
	float4 colorDiffuse = In.diffuse;

	//合成
	float4 color = colorTexture * colorDiffuse;

	//色を赤っぽく変化させる
	if(powerRatio > 0)
	{
		// color.g = color.g * (1 - powerRatio);
		// color.b = color.b * (1 - powerRatio);
		
		color.r = color.r * (1 - powerRatio*filterR);
		color.g = color.g * (1 - powerRatio*filterG);
		color.b = color.b * (1 - powerRatio*filterB);
		
	}

	Out.color = color;

	return Out;
}


//================================================================
//--------------------------------
//technique
technique TecWave
{
	pass P0
	{
		PixelShader = compile ps_3_0 PsWave();
	}
}

