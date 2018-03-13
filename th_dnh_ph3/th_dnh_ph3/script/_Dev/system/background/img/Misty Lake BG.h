
let source = GetCurrentScriptDirectory;

let Empty = source~"blank.png";

let Water = source~"world02.png";
let Seafloor = source~"world02b.png";
let Leaves = source~"world02c2.png";
let Cloud = source~"world02d.png";
let Moon = source~"world02e.png";
let Burst = source~"burstb.png";

let DiveShield = source~"WhirlShield.png";

let Screencover = source~"screencover.png";
let SpellActive = false;

let RunningCondition = true;
let BackgroundActive = true;
let ForceBackgroundActive = false;
let stgtime = 0;
let stgspeed = 2.85;

let LightMod = 0;

let quality = GetCommonData("quality", 2);

let duration = 125;
let LayerTransferCooldown = 90;


let IsUnderwater = false;
let RenderAbove = true;
let RenderBelow = false;


@Initialize{
	SetCommonData("IsPlayerTransferring", false);
	SetCommonData("DiveCount", 0);
	SetCommonData("DiveDuration", duration);
	SetAutoDeleteObject(true);
	StageBg4;
}
@MainLoop{

		if(GetKeyState(KEY_P)==KEY_PUSH){
			WriteLog("Camera Stats:");
			WriteLog("FocusX: " ~ IntToString(GetCameraFocusX));
			WriteLog("FocusY: " ~ IntToString(GetCameraFocusY));
			WriteLog("FocusZ: " ~ IntToString(GetCameraFocusZ));
			
			WriteLog("Azimuth: " ~ IntToString(GetCameraAzimuthAngle));
			WriteLog("Elevation: " ~ IntToString(GetCameraElevationAngle));
			WriteLog("Radius: " ~ IntToString(GetCameraRadius));
			
			WriteLog("Yaw: " ~ IntToString(GetCameraYaw));
			WriteLog("Pitch: " ~ IntToString(GetCameraPitch));
			WriteLog("Roll: " ~ IntToString(GetCameraRoll));
		}
	yield;
}
//Stage 4
task StageBg4{
	BackgroundRenderControl;
	let xpos = 0;
	let ypos = 350;
	let zpos = 280;
	
	let aangle = 90;
	let eangle = 337;
	let radius = 300;
	
	let cam = 0;
	stgspeed = 0.9;
	stgtime = 0.3;
	
	let MoonOriginY = 825;
	
	SetCameraFocusX(xpos);
	SetCameraFocusY(ypos);
	SetCameraFocusZ(zpos);
	SetCameraAzimuthAngle(aangle);
	SetCameraElevationAngle(eangle);
	SetCameraRadius(radius);
	
	
	let ScreenCover = CreateSimple2DImageA1(0.28, Screencover);
	ObjRender_SetPosition(ScreenCover, GetStgFrameWidth/2+32, GetStgFrameHeight/2+16, 0);
	ObjRender_SetColorDouble(ScreenCover, 32, 56, 64, 196, 112, 24);
	ObjRender_SetAlpha(ScreenCover, 86);
	ObjRender_SetPermitCamera(ScreenCover, false);
	Obj_SetVisible(ScreenCover, true);
	
	
	let SkyBG = ObjPrim_Create(OBJ_SPRITE_3D);
	ObjRender_SetBlendType(SkyBG, BLEND_ALPHA);
	ObjRender_SetAlpha(SkyBG, 255);
	ObjPrim_SetTexture(SkyBG, NULL);
	ObjSprite3D_SetSourceRect(SkyBG, 0, 0, 2, 2);
	ObjSprite3D_SetDestRect(SkyBG, -1024, -1024, 1024, 1024);
	ObjRender_SetColor(SkyBG, 255, 255, 0);
	ObjRender_SetPosition(SkyBG, 0, 1424, -300);
	ObjRender_SetAngleXYZ(SkyBG, 90, 0, 0);
	Obj_SetRenderPriority(SkyBG, 0.20);
	ObjRender_SetZWrite(SkyBG, true);
	ObjRender_SetZTest(SkyBG, true);
	
	
	let Ground = ObjPrim_Create(OBJ_SPRITE_3D);
	ObjRender_SetBlendType(Ground, BLEND_ALPHA);
	ObjRender_SetAlpha(Ground, 255);
	ObjPrim_SetTexture(Ground, Seafloor);
	ObjSprite3D_SetSourceRect(Ground, 0, 0, 1024, 1024);
	ObjSprite3D_SetDestRect(Ground, -512, 0, 512, 1024);
	ObjRender_SetPosition(Ground, 0, 200, -300);
	ObjRender_SetColorDouble(Ground, 64, 64, 96, 128, 128, 128);
	Obj_SetRenderPriority(Ground, 0.21);
	ObjRender_SetZWrite(Ground, true);
	ObjRender_SetZTest(Ground, true);
	
	let MoonR = ObjPrim_Create(OBJ_SPRITE_3D);
	ObjRender_SetBlendType(MoonR, BLEND_ADD_ARGB);
	ObjPrim_SetTexture(MoonR, Moon);
	ObjSprite3D_SetSourceRect(MoonR, 0, 0, 512, 512);
	ObjSprite3D_SetDestRect(MoonR, -96, -128, 96, 256);
	ObjRender_SetPosition(MoonR, -96, 825, -95);
	ObjRender_SetAlpha(MoonR, 80);
	Obj_SetRenderPriority(MoonR, 0.23);
	ObjRender_SetAngleXYZ(MoonR, 0, 0, 182);
	
	let Water1 = CreateWaterObject;
	ObjRender_SetPosition(Water1, 0, 512, -100);
	
	let Water2 = CreateWaterObject;
	ObjRender_SetPosition(Water2, 0, 512, -105);
	ObjRender_SetAngleXYZ(Water2, 0, 0, 90);
	
	ascent(i in 0..2){
		CreateUnderWaterSegment(-500+1000*i, 2);
	}
	
	
	// let Leaves1 = CreateWaterObject;
	// ObjRender_SetBlendType(Water1, BLEND_ALPHA);
	// ObjPrim_SetTexture(Leaves1, Leaves);
	// ObjRender_SetPosition(Leaves1, 0, 512, -115);
	
	
	
	
	let defFog = [1100, 1600, 128, 128, 96];
	
	
	SetFogEnable(true);
	SetFogParam(defFog[0], defFog[1], defFog[2], defFog[3], defFog[4]);
	
	
	
	// CameraFlight;
	CreateCloudsB4;
	WaterLayerProperties;
	
	while(RunningCondition){
		RenderBG;
		yield;
	}
	Obj_Delete(ScreenCover);
	CloseScript(GetOwnScriptID);
	
	sub RenderBG{
		// LightMod = max(0, LightMod-0.005);
		cam+=stgspeed*0.6; //remake the camera angles
		let xm = cam*0.55;
		ObjSprite3D_SetSourceRect(Ground, 0, xm, 1024, 1024+xm);
		
		ObjSprite3D_SetSourceRect(Water1, xm, cam, 768+xm, 768+cam);
		
		ObjSprite3D_SetSourceRect(Water2, xm*0.8, cam, 768+xm*0.8, 768+cam);
		
		
		// let lm = 1024*cos(xm*0.4);
		// ObjSprite3D_SetSourceRect(Leaves1, lm, cam, 512+lm, 512+cam);
		
		Obj_SetVisible(SkyBG, BackgroundActive);
		Obj_SetVisible(Ground, BackgroundActive&&RenderAbove);
		Obj_SetVisible(Water1, BackgroundActive&&RenderAbove);
		Obj_SetVisible(Water2, BackgroundActive&&RenderAbove);
		Obj_SetVisible(MoonR, BackgroundActive&&RenderAbove);
		// SetCameraFocusX(xpos+sin(cam*0.05)*20);
		// SetCameraFocusY(ypos+sin(cam*0.05+144)*20);
		// SetCameraFocusZ(zpos+sin(cam*0.05+70)*10);
		// SetCameraRoll(sin(cam*0.2+90)*0.5);
		// SetCameraPitch(sin(cam*0.12+180)*3);
		// SetCameraYaw(sin(cam*0.2+90)*4);
	}
	
	
	
	task WaterLayerProperties{
	
		let MaxLayer = GetCommonData("DiveLayerMax", 1);
		let LocalLayer = MaxLayer;
		let LastLayer = LocalLayer;
		
		
		
		//max layer = over
		// 0 layer = under
		
		
		while(RunningCondition){
		
		
			if(GetCommonData("FiredDive", false)){
				SetCommonData("FiredDive", false);
				LocalLayer++;
				if(LocalLayer > MaxLayer){LocalLayer = 0;}
			}
			
		
			if(LastLayer != LocalLayer){
				GivePlayerShield(duration*1.1);
				if(LocalLayer != MaxLayer){
					if(!IsUnderwater){
						DoUnderWaterStuff;
						IsUnderwater = true;
					}
				}else{
					if(IsUnderwater){
						IsUnderwater = false;
					}
				}
				LastLayer = LocalLayer;
			}
			yield;
		}
		
		task GivePlayerShield(sdur){
			let Shield = CreateSimple2DImageA1(0.5, DiveShield);
			ObjRender_SetBlendType(Shield, BLEND_ADD_ARGB);
			ObjRender_SetColor(Shield, 192, 192, 255);
			ObjRender_SetAlpha(Shield, 255);
			
			ObjRender_SetScaleXYZ(Shield, 2, 2, 1);
			
			let rang = rand(0, 360);
			
			let invtime = sdur*0.18;
			
			let tscl = 2;
			ascent(i in 0..13){
				let mod = i/12;
				ObjRender_SetScaleXYZ(Shield, tscl*mod, tscl*mod, 1);
				DoRender;
			}
			
			sdur-=26;
			loop(sdur){
				DoRender;
			}
			
			descent(i in 0..13){
				let mod = i/12;
				ObjRender_SetScaleXYZ(Shield, tscl*mod, tscl*mod, 1);
				DoRender;
			}
			
			
			Obj_Delete(Shield);
			
			
			sub DoRender{
				rang += 17;
				ObjRender_SetAngleZ(Shield, rang);
				ObjRender_SetPosition(Shield, GetPlayerX, GetPlayerY, 0);
				SetPlayerInvincibilityFrame(max(invtime, GetPlayerInvincibilityFrame));
				yield;
			}
		}
		
		task DoUnderWaterStuff{
			SetCommonData("CanSwapLayer", false);
			yield;
			
			SetCommonData("IsPlayerTransferring", true);
			
			let count = 0;
			
			let iduration = floor(duration*0.6);
			let mduration = round(duration*0.1);
			let eduration = ceil(duration*0.3);
			
			
			// Y + 240
			// ELEVATION + 23
			// Z - 320
			
			let lypos = ypos;
			let lzpos = zpos;
			
			let leang = eangle;
			
			let lmoony = MoonOriginY;
			
			// StartSlow(TARGET_ALL, 20);
			ascent(i in 0..iduration){
				let mod = sin(180/iduration*i);
				
				lypos += 240/iduration*mod*1.9;
				leang += 24/iduration*mod*1.8;
				
				SetCameraFocusY(lypos);
				SetCameraElevationAngle(leang);
				
				lmoony += 285/iduration*mod*1.5;
				ObjRender_SetY(MoonR, lmoony);
				
				lzpos-=mod;
				
				SetCameraFocusZ(lzpos);
				
				
				DoCountYield;
			}
			
			ObjRender_SetY(MoonR, 3000);
			loop(mduration){DoCountYield;}
			
			
			let Fade = CreateBlankScreen;
			
			ascent(i in 0..eduration){
				let mod = sin(90*i/eduration);
				lzpos -= 15*mod;
				ObjRender_SetAlpha(Fade, 255*mod);
				SetCameraFocusZ(lzpos);
				DoCountYield;
			}
			
			let Splash = CreateBurstScreen;
						
			
			SetFogParam(450, 800, 32, 48, 64);
			if(quality < 2){SetFogParam(450, defFog[1], 32, 48, 64);}
			RenderAbove = false;
			RenderBelow = true;
			SetCommonData("IsPlayerTransferring", false);
			count = 0;
			
			SetCameraFocusZ(0);
			NotifyEventAll(EV_USER+177, 0);
			ascent(i in 0..10){
				CreateFadingOutScreencover(128, 144, 224, 35+10*i);
			}
			descent(i in 0..22){
				let mod = sin(90/22*i);
				let col = 255*mod;
				ObjRender_SetAlpha(Fade, col);
				ObjRender_SetColor(Splash, col, col, col);
				yield;
			}
			
			Obj_Delete(Fade);
			Obj_Delete(Splash);
			
			loop(LayerTransferCooldown){yield;}
			SetCommonData("CanSwapLayer", true);
			
			
			// ObjRender_SetAlpha(MoonR, 48);
			// ObjRender_SetScaleXYZ(MoonR, 3, 3, 1);
			
			
			while(IsUnderwater){
				yield;
			}
			SetCommonData("IsPlayerTransferring", true);
			SetCommonData("CanSwapLayer", false);
			
			Fade = CreateBlankScreen;
			
			lzpos = 0;
			ascent(i in 0..iduration){
				let mod = sin(90*i/iduration);
				lzpos += 9*mod;
				SetCameraFocusZ(lzpos);
				ObjRender_SetAlpha(Fade, 255*(max(0, i/iduration*2-1)));
				DoCountYield;
			}
			
			
			loop(mduration){DoCountYield;}
			
			SetCameraFocusX(xpos);
			SetCameraFocusY(ypos);
			SetCameraFocusZ(zpos);
			SetCameraAzimuthAngle(aangle);
			SetCameraElevationAngle(eangle);
			SetCameraRadius(radius);
			SetFogParam(defFog[0], defFog[1], defFog[2], defFog[3], defFog[4]);
			ObjRender_SetY(MoonR, MoonOriginY);
			
			NotifyEventAll(EV_USER+177, 0);
			RenderAbove = true;
			RenderBelow = false;
			
			ascent(i in 0..10){
				CreateFadingOutScreencover(128, 144, 224, 35+12*i);
			}
			Splash = CreateBurstScreen;
			
			SetCommonData("IsPlayerTransferring", false);
			
			descent(i in 0..eduration){
				let mod = i/eduration;
				let col = 255*mod;
				ObjRender_SetColor(Splash, col, col, col);
				SetCameraFocusZ(zpos/2+zpos/2*(1-mod));
				ObjRender_SetAlpha(Fade, 255*(max(0, i/eduration*2-1)));
				DoCountYield;
			}
			
			Obj_Delete(Fade);
			Obj_Delete(Splash);
			
			loop(LayerTransferCooldown){yield;}
			SetCommonData("CanSwapLayer", true);
			
			function DoCountYield{
				SetCommonData("DiveCount", count);
				count++;
				yield;
			}
			
		}
		
	}
	
	
	
	function CreateWaterObject{
		let Water1 = ObjPrim_Create(OBJ_SPRITE_3D);
		ObjRender_SetBlendType(Water1, BLEND_ADD_ARGB);
		ObjRender_SetAlpha(Water1, 128);
		ObjPrim_SetTexture(Water1, Water);
		ObjSprite3D_SetSourceRect(Water1, 0, 0, 512, 512);
		ObjSprite3D_SetDestRect(Water1, -512, -512, 512, 512);
		ObjRender_SetColorDouble(Water1, 128, 128, 128, 96, 96, 128);
		Obj_SetRenderPriority(Water1, 0.22);
		// ObjRender_SetZWrite(Water1, true);
		// ObjRender_SetZTest(Water1, true);
		return Water1;
	}
	
	task CreateUnderWaterSegment(buy, maxn){
	
	
		let Uscl = 5;
		let BUY = buy;
	
		let lm = 0;
		let Under = ID_INVALID;
		if(quality>=2){
			Under = ObjMesh_Create;
			ObjMesh_Load(Under, source~"underwater.mqo");
			Obj_SetRenderPriority(Under, 0.21);
			ObjRender_SetAngleXYZ(Under, 90, 0, 0);
			ObjRender_SetScaleXYZ(Under, Uscl, Uscl, Uscl);
		}else{
			Under = ObjPrim_Create(OBJ_SPRITE_3D);
			ObjRender_SetAlpha(Under, 255);
			ObjPrim_SetTexture(Under, Seafloor);
			ObjSprite3D_SetSourceRect(Under, 0, 0, 1024, 1024);
			ObjSprite3D_SetDestRect(Under, -512, 0, 512, 1024);
			ObjRender_SetColorDouble(Under, 64, 64, 96, 128, 128, 128);
			Obj_SetRenderPriority(Under, 0.21);
			ObjRender_SetZWrite(Under, true);
			ObjRender_SetZTest(Under, true);
			lm = -400;
		}
		
		// 200+100*Uscl;
		ObjRender_SetPosition(Under, 0, BUY, -300);
		
		
		while(RunningCondition){
			BUY-=stgspeed;
			if(BUY < -500){BUY += 1000*maxn;}
			ObjRender_SetY(Under, BUY+lm);
			Obj_SetVisible(Under, BackgroundActive&&RenderBelow);
			yield;
		}
	}
}


task ObjRender_SetColorDouble(obj, r1, g1, b1, r2, g2, b2){
	//the 2 versions are additive multipled by LightMod
	
	while(!Obj_IsDeleted(obj)){
		ObjRender_SetColor(obj, r1 + r2*LightMod, g1 + g2*LightMod, b1 + b2*LightMod);
		yield;
	}
}




task CreateFadingOutScreencover(r, g, b, duration){
	let ScreenCover = CreateSimple2DImageA1(0.28, Screencover);
	ObjRender_SetBlendType(ScreenCover, BLEND_ADD_ARGB);
	ObjRender_SetPosition(ScreenCover, GetStgFrameWidth/2+32, GetStgFrameHeight/2+16, 0);
	ObjRender_SetColor(ScreenCover, 32, 56, 64);
	ObjRender_SetAlpha(ScreenCover, 192);
	ObjRender_SetPermitCamera(ScreenCover, false);
	Obj_SetVisible(ScreenCover, true);
	
	let idur = floor(duration*0.15);
	let edur = ceil(duration*0.85);
	
	ascent(i in 0..idur){
		let mod = 1/duration*i;
		ObjRender_SetColor(ScreenCover, r*mod, g*mod, b*mod);
		yield;
	}
	
	descent(i in 0..idur){
		let mod = 1/duration*i;
		ObjRender_SetColor(ScreenCover, r*mod, g*mod, b*mod);
		yield;
	}
	Obj_Delete(ScreenCover);
}

task CreateCloudsB4{
	if(quality == 0){return;}
	while(RunningCondition){
		FireCloudA1([-300, 300, 90], 	rand(800, 900), 	125, 
					rand(-0.25, 0.25), 		rand(-2, -1.5), 		rand(-0.6, 0.2), 
					rand(164, 192));
		loop(22){yield;}
	}
	
	
	task FireCloudA1(xp, y, z, xm, ym, zm, time){
		let cloub = Create3DProperties(96, 256, Cloud, 0.23);
		ObjRender_SetBlendType(cloub, BLEND_ADD_ARGB);
		ObjSprite3D_SetBillboard(cloub, true);
		ObjRender_SetColor(cloub, 48, 64, 96);
		
		let x = rand(xp[0], xp[1]);
		
		while(absolute(x) < xp[2]){
			x = rand(xp[0], xp[1]);
		}
		
		
		
		let az = rand(0, 360);
		let azm = rand(-1, 1)*0.4;
		
		
		let itime = floor(time*0.2);
		let rtime = round(time*2);
		let etime = ceil(time*0.7);
		
		
		ascent(i in 0..itime){
			RenderCloud;
			let scl = 0.35/(itime-1)*i;
			ObjRender_SetScaleXYZ(cloub, scl, scl, scl);
			yield;
		}
		
		ascent(i in 0..rtime){
			RenderCloud;
			yield;
		}
		
		descent(i in 0..etime){
			RenderCloud;
			let scl = 0.35/(etime-1)*i;
			ObjRender_SetScaleXYZ(cloub, scl, scl, scl);
			yield;
		}
		
		Obj_Delete(cloub);
		
		sub RenderCloud{
			Obj_SetVisible(cloub, BackgroundActive && RenderAbove);
			x+=xm;
			y+=ym;
			z+=zm;
			az+=azm;
			
			ObjRender_SetPosition(cloub, x, y, z);
			
			ObjRender_SetAngleXYZ(cloub, 0, 0, az);
			
		}
		
		
	}
}



task BackgroundRenderControl{
	let fade = 0;
	while(RunningCondition){
		if(SpellActive){
			fade++;
		}else{fade = 0;}
		
		if(fade < 140||ForceBackgroundActive){
			BackgroundActive = true;
		}else{BackgroundActive = false;}
		
		yield;
	}
}


function CreateBlankScreen{
	let Fade = ObjPrim_Create(OBJ_SPRITE_2D);
	Obj_SetRenderPriority(Fade, 0.28);
	ObjPrim_SetTexture(Fade, Empty);
	ObjSprite2D_SetSourceRect(Fade, 0, 0, 16, 16);
	ObjSprite2D_SetDestRect(Fade, 32, 16, GetStgFrameWidth+32, GetStgFrameHeight+16);
	ObjRender_SetColor(Fade, 0, 0, 0);
	ObjRender_SetAlpha(Fade, 0);
	ObjRender_SetPermitCamera(Fade, false);
	return Fade;
}

function CreateBurstScreen{
	let Splash = ObjPrim_Create(OBJ_SPRITE_2D);
	ObjRender_SetBlendType(Splash, BLEND_ADD_ARGB);
	Obj_SetRenderPriority(Splash, 0.26);
	ObjPrim_SetTexture(Splash, Burst);
	ObjSprite2D_SetSourceRect(Splash, 0, 0, 512, 512);
	ObjSprite2D_SetDestRect(Splash, 32, 16, GetStgFrameWidth+32, GetStgFrameHeight+16);
	ObjRender_SetPermitCamera(Splash, false);
	return Splash;
}


function Create3DBrush(alpha, srcrect, offset, image, priority){
	let StageProp = ObjPrim_Create(OBJ_SPRITE_3D);
	ObjRender_SetBlendType(StageProp, BLEND_ALPHA);
	ObjRender_SetAlpha(StageProp, alpha);
	ObjPrim_SetTexture(StageProp, image);
	Obj_SetRenderPriority(StageProp, priority);
	ObjSprite3D_SetSourceRect(StageProp, 0+offset, 0+offset, srcrect+offset, srcrect+offset);
	ObjSprite3D_SetDestRect(StageProp, 0, -srcrect/2, srcrect, srcrect/2); // Centered middle origin maybe
	//ObjRender_SetZWrite(StageProp, true);
	//ObjRender_SetZTest(StageProp, true);
	return StageProp;
}
function Create3DProperties(alpha, srcrect, image, priority){
	let StageProp = ObjPrim_Create(OBJ_SPRITE_3D);
	ObjRender_SetBlendType(StageProp, BLEND_ALPHA);
	ObjRender_SetAlpha(StageProp, alpha);
	ObjPrim_SetTexture(StageProp, image);
	Obj_SetRenderPriority(StageProp, priority);
	ObjSprite3D_SetSourceRect(StageProp, 0, 0, srcrect, srcrect);
	ObjSprite3D_SetDestRect(StageProp, -srcrect, -srcrect, srcrect, srcrect);
	// ObjRender_SetZWrite(StageProp, true);
	// ObjRender_SetZTest(StageProp, true);
	return StageProp;
}

function Create3DEnvironment(image, srcrect, pri){
	let StageProp = ObjPrim_Create(OBJ_SPRITE_3D);
	ObjRender_SetBlendType(StageProp, BLEND_ALPHA);
	ObjRender_SetY(StageProp, -64);
	ObjPrim_SetTexture(StageProp, image);
	Obj_SetRenderPriority(StageProp, pri);
	ObjSprite3D_SetSourceRect(StageProp, 0, 0, srcrect*4, srcrect*4);
	ObjSprite3D_SetDestRect(StageProp, -srcrect*2, 0, srcrect*2, srcrect*4);
	ObjRender_SetZWrite(StageProp, true);
	ObjRender_SetZTest(StageProp, true);
	return StageProp;
}

task BackgroundShakeA1(intensity, intdec){
	while(intensity>0){
		Set2DCameraFocusX(GetStgFrameWidth/2 + rand(-intensity, intensity));
		Set2DCameraFocusY(GetStgFrameHeight/2 + rand(-intensity, intensity));
		SetCameraFocusX(rand(-intensity, intensity));
		SetCameraFocusZ(100+rand(-intensity, intensity));
		intensity-=intdec;
		yield;
	}
	SetCameraFocusX(0);
	SetCameraFocusZ(100);
	Reset2DCamera;
	yield;
}

task CameraFlight{
	// Static Version
	let pos = [GetCameraFocusX,GetCameraFocusY,GetCameraFocusZ];
	let ang = [GetCameraAzimuthAngle,GetCameraElevationAngle,GetCameraRadius];
	let pln = [GetCameraYaw, GetCameraPitch, GetCameraRoll];
	let cammod = 1.25;
	loop{
		if(GetKeyState(KEY_J)==KEY_HOLD){pos[0]=pos[0]+5*cammod;}
		if(GetKeyState(KEY_L)==KEY_HOLD){pos[0]=pos[0]-5*cammod;}
		if(GetKeyState(KEY_I)==KEY_HOLD){pos[1]=pos[1]+5*cammod;}
		if(GetKeyState(KEY_K)==KEY_HOLD){pos[1]=pos[1]-5*cammod;}
		if(GetKeyState(KEY_U)==KEY_HOLD){pos[2]=pos[2]-5*cammod;}
		if(GetKeyState(KEY_O)==KEY_HOLD){pos[2]=pos[2]+5*cammod;}
		
		
		if(GetKeyState(KEY_Q)==KEY_HOLD){ang[0]=ang[0]+2*cammod;}
		if(GetKeyState(KEY_E)==KEY_HOLD){ang[0]=ang[0]-2*cammod;}
		if(GetKeyState(KEY_W)==KEY_HOLD){ang[1]=ang[1]+2*cammod;}
		if(GetKeyState(KEY_S)==KEY_HOLD){ang[1]=ang[1]-2*cammod;}
		if(GetKeyState(KEY_A)==KEY_HOLD){ang[2]=ang[2]+2*cammod;}
		if(GetKeyState(KEY_D)==KEY_HOLD){ang[2]=ang[2]-2*cammod;}
		
		if(GetKeyState(KEY_NUMPAD4)==KEY_HOLD){pln[0]=pln[0]+cammod;}
		if(GetKeyState(KEY_NUMPAD6)==KEY_HOLD){pln[0]=pln[0]-cammod;}
		if(GetKeyState(KEY_NUMPAD5)==KEY_HOLD){pln[1]=pln[1]+cammod;}
		if(GetKeyState(KEY_NUMPAD2)==KEY_HOLD){pln[1]=pln[1]-cammod;}
		if(GetKeyState(KEY_NUMPAD3)==KEY_HOLD){pln[2]=pln[2]+cammod;}
		if(GetKeyState(KEY_NUMPAD1)==KEY_HOLD){pln[2]=pln[2]-cammod;}
		
		
		
		
		SetCameraFocusX(pos[0]);
		SetCameraFocusY(pos[1]);
		SetCameraFocusZ(pos[2]);
		SetCameraAzimuthAngle(ang[0]);	
		SetCameraElevationAngle(ang[1]);
		SetCameraRadius(ang[2]);
		
		SetCameraYaw(pln[0]);
		SetCameraPitch(pln[1]);
		SetCameraRoll(pln[2]);
		
		yield;
	}
}

function GetDistance(x1,y1,x2,y2){
	return(((x2-x1)^2+(y2-y1)^2)^(1/2))
}

function CreateSimple2DImageA1(pri, image){
	let obj = ObjPrim_Create(OBJ_SPRITE_2D);
	ObjRender_SetBlendType(obj, BLEND_ALPHA);
	Obj_SetRenderPriority(obj, pri);
	ObjPrim_SetTexture(obj, image);
	let test = [GetTextureWidth(image), GetTextureHeight(image)];
	ObjSprite2D_SetSourceRect(obj, 0, 0, test[0]-1, test[1]-1);
	ObjSprite2D_SetDestRect(obj, -(test[0]/2+0.5), -(test[1]/2), (test[0]/2), (test[1]/2));
	return obj;
}


task PlaySoundA1(name){
	let ID = -1;
	let GlobalSounds = GetCommonData("GlobalSoundData", [-1]);
	let GlobalSndStr = GetCommonData("GlobalSndStrData", [-1]);
	ascent(i in 0..length(GlobalSndStr)){
		if(GlobalSndStr[i]==name){ID = i; break;}
	}
	if(ID==-1){RaiseError("Error when attempting to play audio: "~name);}
	ObjSound_Play(GlobalSounds[ID]);
}

