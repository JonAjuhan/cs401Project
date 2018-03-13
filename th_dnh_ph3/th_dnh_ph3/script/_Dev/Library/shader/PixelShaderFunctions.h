//found in Yuugi by Achy and gtbot
//it's all greek to me atm but it seemed like a good idea to grab it


let IsTimeStoppedPseudo = false;


//let timezonescale = 1.15-argument/360;

task TimeStopL1(r, g, b, bw, spd, duration, minpri, maxpri){
	let RecoveryTime = 14;
	let bspeed = GetCommonData("stgspeed", 4);
	if(quality < 2){ModifyBGSpeedNonShader;return;}
	r = (255-r)/255;
	g = (255-g)/255;
	b = (255-b)/255;
	
	let pathShader = GetMainStgScriptDirectory~"ds_system/shader/colorTint.hlsl";
	
	let objShader = ObjPrim_Create(OBJ_SPRITE_2D);
	ObjShader_SetShaderF(objShader, pathShader);
	ObjShader_SetTechnique(objShader, "TecColor");
	ObjShader_SetFloat(objShader, "s_bw", bw);

	SetShaderI(objShader, minpri, maxpri);
	
	ModifyBGSpeedShader;
	
	ascent(i in 0..duration-RecoveryTime){
		if(!Hold(1)){break;}
	}	
	ascent(i in 0..RecoveryTime){
		if(!Hold(1)){break;}
	}
	
	ObjShader_ResetShader(objShader);
	ResetShaderI(minpri, maxpri);
	Obj_Delete(objShader);
	
	
	task ModifyBGSpeedShader{
		if(bw == 0){
			let targetspd = spd-bspeed;
			let targetclock = spd-1;
			ascent(i in 0..RecoveryTime){
				ObjShader_SetFloat(objShader, "s_red", 1-r/RecoveryTime*i);
				ObjShader_SetFloat(objShader, "s_green", 1-g/RecoveryTime*i);
				ObjShader_SetFloat(objShader, "s_blue", 1-b/RecoveryTime*i);
				SetCommonData("stgspeed", bspeed+targetspd/RecoveryTime*i);
				SetCommonData("clockspeed", 1+targetclock/RecoveryTime*i);
				if(!Hold(1)){break;}
			}
			ascent(i in 0..duration-RecoveryTime*2){if(!Hold(1)){break;}}
			descent(i in 0..RecoveryTime){
				ObjShader_SetFloat(objShader, "s_red", 1-r/RecoveryTime*i);
				ObjShader_SetFloat(objShader, "s_green", 1-g/RecoveryTime*i);
				ObjShader_SetFloat(objShader, "s_blue", 1-b/RecoveryTime*i);
				SetCommonData("stgspeed", bspeed+targetspd/RecoveryTime*i);
				SetCommonData("clockspeed", 1+targetclock/RecoveryTime*i);
				if(!Hold(1)){break;}
			}
		}else{
			SetCommonData("stgspeed", 0);
			SetCommonData("clockspeed", 0);
			ObjShader_SetFloat(objShader, "s_red", 1);
			ascent(i in 0..duration-RecoveryTime){if(!Hold(1)){break;}}
			ascent(i in 0..RecoveryTime){
				ObjShader_SetFloat(objShader, "s_red", 1-1/RecoveryTime*i);
				SetCommonData("stgspeed", bspeed/RecoveryTime*i);
				SetCommonData("clockspeed", 1/RecoveryTime*i);
				if(!Hold(1)){break;}
			}
		}
		SetCommonData("stgspeed", bspeed);
	}
	
	task ModifyBGSpeedNonShader{
		let obj = ObjPrim_Create(OBJ_SPRITE_2D);
		ObjRender_SetBlendType(obj, BLEND_ADD_RGB);
		ObjRender_SetAlpha(obj, 255);
		Obj_SetRenderPriority(obj, maxpri);
		ObjPrim_SetTexture(obj, NULL);
		ObjSprite2D_SetSourceRect(obj, 0, 0, 2, 2);
		ObjSprite2D_SetDestRect(obj, 32, 16, GetStgFrameWidth+32, GetStgFrameHeight+16);
		ObjRender_SetPermitCamera(obj, false);
		
		
		let palph = 0;
		ObjRender_SetColor(obj, r*0.2*palph, g*0.2*palph, b*0.2*palph);
		
		if(bw == 0){
			let targetspd = spd-bspeed;
			let targetclock = spd-1;
			ascent(i in 0..RecoveryTime){
				palph = i/RecoveryTime;
				ObjRender_SetColor(obj, r*0.2*palph, g*0.2*palph, b*0.2*palph);
				SetCommonData("stgspeed", bspeed+targetspd/RecoveryTime*i);
				SetCommonData("clockspeed", 1+targetclock/RecoveryTime*i);
				if(!Hold(1)){break;}
			}
			palph = 1;
			ObjRender_SetColor(obj, r*0.2*palph, g*0.2*palph, b*0.2*palph);
			ascent(i in 0..duration-RecoveryTime*2){if(!Hold(1)){break;}}
			descent(i in 0..RecoveryTime){
				palph = i/RecoveryTime;
				ObjRender_SetColor(obj, r*0.2*palph, g*0.2*palph, b*0.2*palph);
				SetCommonData("stgspeed", bspeed+targetspd/RecoveryTime*i);
				SetCommonData("clockspeed", 1+targetclock/RecoveryTime*i);
				if(!Hold(1)){break;}
			}
		}else{
			SetCommonData("stgspeed", 0);
			SetCommonData("clockspeed", 0);
			ObjRender_SetBlendType(obj, BLEND_SUBTRACT);
			palph = 48;
			ObjRender_SetColor(obj, palph, palph, palph);
			ascent(i in 0..duration-RecoveryTime){if(!Hold(1)){break;}}
			ascent(i in 0..RecoveryTime){
				let ralph = palph-palph*i/RecoveryTime;
				ObjRender_SetColor(obj, ralph, ralph, ralph);
				SetCommonData("stgspeed", bspeed/RecoveryTime*i);
				SetCommonData("clockspeed", 1/RecoveryTime*i);
				if(!Hold(1)){break;}
			}
		}
		SetCommonData("stgspeed", bspeed);
		Obj_Delete(obj);
	}
}

/*
task TimeStopL2(duration){
	//Background is render targetted; mask will "remove" the timestop
	//No quality setting consideration, slightly outdated code, needs improvements
	let bspeed = GetCommonData("stgspeed", 3);
	
	let RecoveryTime = 12;
	let minpri = 20;
	let maxpri = 29;
	
	let renderTexture = "SpellTimeStop";
	let pathShader = GetMainStgScriptDirectory~"ds_system/shader/monochrome.hlsl";
	let pathMask = GetMainStgScriptDirectory~"ds_system/img/Masks/circlefdr.png";
	let pathMaskBG = GetMainStgScriptDirectory~"ds_system/img/Masks/blank.png";
	if(!CreateRenderTarget(renderTexture)){
	RaiseError("Not enough VRAM to proceed.\nTry restarting the game and lowering the graphics quality.");}
		
	SetInvalidRenderPriorityA1(minpri, maxpri);
	Reset2DCamera;
	RenderToTextureA1(renderTexture, minpri, maxpri, true);
	ClearInvalidRenderPriority;
	
	let objShader = ObjPrim_Create(OBJ_SPRITE_2D);
	ObjShader_SetShaderF(objShader, pathShader);
	ObjShader_SetTechnique(objShader, "TecMask");

	ObjShader_SetTexture(objShader, "textureMask_", renderTexture);
	SetShaderI(objShader, maxpri, maxpri);
	
	IsTimeStoppedPseudo = true;
	
	CreateTimeField(GetPlayerObjectID, timezonescale);
	
	let frame = 0;
	let sint = 0.003;
	SetCommonData("stgspeed", 0);
	ascent(i in 0..duration-RecoveryTime){
		if(EnemyDead){break;}
		PerformProperties;
		yield;
	}
	
	IsTimeStoppedPseudo = false;
	
	ascent(i in 0..RecoveryTime){
		SetCommonData("stgspeed", bspeed/RecoveryTime*i);
		PerformProperties;
		yield;
	}
	SetCommonData("stgspeed", bspeed);
	
	ObjShader_ResetShader(objShader);
	ResetShaderI(maxpri, maxpri);
	RemoveTexture(renderTexture);
	Obj_Delete(objShader);
	
	
	sub PerformProperties{
		frame++;
		ObjShader_SetFloat(objShader, "p_frame", frame);
		ObjShader_SetFloat(objShader, "p_int", sint);
	}
	
	task CreateTimeField(dobj, scl){
		yield;
		let obj = ObjPrim_Create(OBJ_SPRITE_2D);
		ObjRender_SetBlendType(obj, BLEND_ALPHA);
		Obj_SetRenderPriority(obj, maxpri/100);
		ObjPrim_SetTexture(obj, pathMask);
		ObjSprite2D_SetSourceRect(obj, 0, 0, 1024, 1024);
		ObjSprite2D_SetDestCenter(obj);
		ObjRender_SetScaleXYZ(obj, scl, scl, scl);
		
		while(IsTimeStoppedPseudo){
			ObjRender_SetPosition(obj, ObjMove_GetX(dobj), ObjMove_GetY(dobj), 0);
			yield;
		}
		descent(i in 0..RecoveryTime){
			ObjRender_SetAlpha(obj, 255/RecoveryTime*i);
			ObjRender_SetPosition(obj, ObjMove_GetX(dobj), ObjMove_GetY(dobj), 0);
			yield;
		}
		
		Obj_Delete(obj);
	}	
}

*/

task ColorWarpA1(minpri, maxpri, period, horiz, verti){
	if(quality < 2){return;}
	
	let pathShader = GetMainStgScriptDirectory~"ds_system/shader/colorRainbow.hlsl";
	
	let objShader = ObjPrim_Create(OBJ_SPRITE_2D);
	ObjShader_SetShaderF(objShader, pathShader);
	ObjShader_SetTechnique(objShader, "TecRainbow");
	ObjShader_SetFloat(objShader, "s_period", period);
	ObjShader_SetFloat(objShader, "s_horiz", horiz);
	ObjShader_SetFloat(objShader, "s_verti", verti);
	ObjShader_SetFloat(objShader, "s_angle", 0);
	

	SetShaderI(objShader, minpri, maxpri);
	
	let frame = 0;
	
	loop{
		ObjShader_SetFloat(objShader, "s_angle", frame);
		frame+=5;
		yield;
	}
	
	ObjShader_ResetShader(objShader);
	ResetShaderI(minpri, maxpri);
	Obj_Delete(objShader);
}	


