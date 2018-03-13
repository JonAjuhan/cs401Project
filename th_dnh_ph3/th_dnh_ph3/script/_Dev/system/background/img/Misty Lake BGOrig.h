
let source = GetCurrentScriptDirectory;

//this has gone out of control help
let stbg0 = source~"stg0.png";
let stbg1 = source~"world02.png";
let stbg2 = source~"world02b.png";
let stbg3 = source~"world02c.png";
let stbg4 = source~"world02c2.png";
let stbg5 = source~"world02d.png";
let stbg6 = source~"world02e.png";
let stbg7 = source~"world02s.png";
let stbg8 = source~"glare.png";
let stbg9 = source~"screencover.png";
let stgspeed = 2.85;
let clouds = 0;
let sun;
let glare = [ID_INVALID, 0];
let gcount = 0;
let gacount = 0;
let SpellActive = false;

@Initialize{
	SetAutoDeleteObject(true);
	Stage1Bg;
}
@MainLoop{
	yield;
}

task Stage1Bg{
	let bg1size = 256;
	let ypos = 0;
	let xpos = 0;
	let wpos = 0;
	let cam = 0;
	
	
	SetCameraFocusX(0);
	SetCameraFocusY(0);
	SetCameraFocusZ(100);
	SetCameraRadius(300);
	SetCameraElevationAngle(310);
	SetCameraAzimuthAngle(90);		
	
	let StageBGSky = ObjPrim_Create(OBJ_SPRITE_3D);
	ObjRender_SetBlendType(StageBGSky, BLEND_ALPHA);
	ObjRender_SetAlpha(StageBGSky, 255);
	ObjPrim_SetTexture(StageBGSky, NULL);
	ObjSprite3D_SetSourceRect(StageBGSky, 0, 0, 0, 0);
	ObjSprite3D_SetDestRect(StageBGSky, -bg1size*2.5, 0, bg1size*2.5, bg1size*4);
	ObjRender_SetColor(StageBGSky, 128, 128, 255);
	ObjRender_SetFogEnable(StageBGSky, true);
	ObjRender_SetPosition(StageBGSky, 0, 1000, -500);
	ObjRender_SetAngleXYZ(StageBGSky, 90, 0, 0);
	Obj_SetRenderPriority(StageBGSky, 0.71);
	ObjRender_SetZWrite(StageBGSky, true);
	ObjRender_SetZTest(StageBGSky, true);
	
	let StageBG1a = Create3DEnvironment(stbg2, 256, 0.71); //Ground
	ObjRender_SetPosition(StageBG1a, 0, -96, -112);
	ObjRender_SetColor(StageBG1a, 128, 128, 208);
	ObjRender_SetZWrite(StageBG1a, false);
	ObjRender_SetZTest(StageBG1a, false);
	
	let StageBG2a = Create3DEnvironment(stbg1, 256, 0.74); //Water
	ObjRender_SetBlendType(StageBG2a, BLEND_ALPHA);
	ObjRender_SetPosition(StageBG2a, 0, -96, -24);
	ObjRender_SetAlpha(StageBG2a, 96);
	ObjRender_SetColor(StageBG2a, 192, 192, 255);
	ObjRender_SetZWrite(StageBG2a, false);
	ObjRender_SetZTest(StageBG2a, false);
	
	let StageBG2b = Create3DEnvironment(stbg1, 256, 0.74); //Water
	ObjRender_SetBlendType(StageBG2b, BLEND_ALPHA);
	ObjRender_SetPosition(StageBG2b, 0, -96, -30);
	ObjRender_SetAlpha(StageBG2b, 96);
	ObjRender_SetColor(StageBG2b, 192, 192, 255);
	ObjRender_SetZWrite(StageBG2b, false);
	ObjRender_SetZTest(StageBG2b, false);
	
	let StageBG2c1 = Create3DEnvironment(stbg3, 256, 0.74); //Plant Stems
	ObjRender_SetPosition(StageBG2c1, 0, -96, -23);
	ObjRender_SetAlpha(StageBG2c1, 192);
	ObjRender_SetColor(StageBG2c1, 80, 80, 112);
	Obj_SetVisible(StageBG2c1, false);
	
	let StageBG2c2 = Create3DEnvironment(stbg4, 256, 0.74); //Leaves
	ObjRender_SetPosition(StageBG2c2, 0, -96, -22);
	ObjRender_SetAlpha(StageBG2c2, 192);
	ObjRender_SetColor(StageBG2c2, 80, 80, 112);
	Obj_SetVisible(StageBG2c2, false);
	
	let StageBGd1 = Create3DBrush(255, 512, 0, stbg6, 0.73); //SUN
	ObjSprite3D_SetDestRect(StageBGd1, -64, -64, 64, 64);
	ObjRender_SetBlendType(StageBGd1, BLEND_ADD_ARGB);
	ObjRender_SetPosition(StageBGd1, -128, 400, 224);
	ObjRender_SetAngleXYZ(StageBGd1, 90, 0, 0);
	sun = GetObject2dPosition(StageBGd1);
	
	let StageBGd4 = CreateSimple2DImageA1(0.77, stbg9);
	ObjRender_SetBlendType(StageBGd4, BLEND_ADD_ARGB);
	ObjRender_SetPosition(StageBGd4, GetStgFrameWidth/2+32, GetStgFrameHeight/2+16, 0);
	ObjRender_SetAlpha(StageBGd4, 144);
	ObjRender_SetColor(StageBGd4, 176, 224, 230);
	ObjRender_SetPermitCamera(StageBGd4, false);
	
	/*
	let StageBGd3 = CreateSimple2DImageA1(0.76, stbg8);
	ObjRender_SetBlendType(StageBGd3, BLEND_ADD_RGB);
	ObjRender_SetScaleXYZ(StageBGd3, 0.65, 0.65, 0.65);
	ObjRender_SetPosition(StageBGd3, GetStgFrameWidth/2+64, GetStgFrameHeight/2-16, 0);
	ObjRender_SetColor(StageBGd3, glare[1], glare[1], glare[1]);
	ObjRender_SetPermitCamera(StageBGd3, false);
	glare[0] = StageBGd3;
	*/
	
	
	
	let StageBGd2 = Create3DBrush(255, 512, 0, stbg6, 0.73); //SUN Reflection
	ObjSprite3D_SetDestRect(StageBGd2, -64, -160, 64, 304);
	ObjRender_SetColor(StageBGd2, 64, 64, 64);
	ObjRender_SetBlendType(StageBGd2, BLEND_ADD_ARGB);
	ObjRender_SetPosition(StageBGd2, -128, 300, -20);
	ObjRender_SetAngleXYZ(StageBGd2, 0, 0, 182);
	ObjRender_SetAlpha(StageBGd2, 80);
	
		
	SetFogEnable(true);
	SetFogParam(500, 800, 128, 144, 192);
	CreateBrushGroupA1;
	
	//CameraFlight;
	SetCommonData("SelectionSet", true);
	while(!GetCommonData("SelectionSet", false)){RenderBG;yield;}
	Obj_SetRenderPriority(StageBG1a, 0.21);
	Obj_SetRenderPriority(StageBG2a, 0.24);
	Obj_SetRenderPriority(StageBG2b, 0.24);
	Obj_SetRenderPriority(StageBG2c1, 0.24);
	Obj_SetRenderPriority(StageBG2c2, 0.24);
	Obj_SetRenderPriority(StageBGd1, 0.23);
	Obj_SetRenderPriority(StageBGd2, 0.23);
	//Obj_SetRenderPriority(StageBGd3, 0.26);
	Obj_SetRenderPriority(StageBGd4, 0.27);
	Obj_SetRenderPriority(StageBGSky, 0.21);
	while(GetCommonData("quality", 2)!=0){
		RenderBG;
		yield;
	}
	Obj_Delete(StageBG1a);
	Obj_Delete(StageBG2a);
	Obj_Delete(StageBG2b);
	Obj_Delete(StageBG2c1);
	Obj_Delete(StageBG2c2);
	Obj_Delete(StageBGd1);
	Obj_Delete(StageBGd2);
	Obj_Delete(StageBGd4);
	Obj_Delete(StageBGSky);
	CloseScript(GetOwnScriptID);
	
	sub RenderBG{
		//ObjRender_SetColor(StageBGd3, glare[1], glare[1], glare[1]);
		let desta = max(min(255-10*gcount^2-4*gacount^2, 255), 0);
		glare[1] = max(min(glare[1]+20, 255), 0);
		if(glare[1]>desta){
			glare[1] = max(glare[1]-20, desta);
		}else if(glare[1]<desta){
			glare[1] = min(glare[1]+20, desta);
		}
		cam+=0.4;
		SetCameraRoll(sin(cam)/2);
		ObjRender_SetX(StageBGd1, -128-16*sin(cam));
		ObjRender_SetY(StageBGd1, 400+10*sin(cam));
		ObjRender_SetAngleZ(StageBGd1, sin(cam)/2);
		ObjRender_SetX(StageBGd2, -128+6*sin(cam));
		ypos+=stgspeed;
		xpos+=0.25;
		//wpos+=cos(cam/3.5)*0.4;
		if(ypos>=1024){ypos = 0;}
		ObjSprite3D_SetSourceRect(StageBG1a, 0, ypos, 1024, 1024+ypos);
		ObjSprite3D_SetSourceRect(StageBG2c1, wpos+xpos, ypos, 1024+wpos+xpos*0.5, 1024+ypos);
		ObjSprite3D_SetSourceRect(StageBG2c2, wpos-xpos, ypos, 1024+wpos-xpos*0.5, 1024+ypos);
		ObjSprite3D_SetSourceRect(StageBG2a, wpos*0.5+xpos, ypos-xpos*0.5, 1024+wpos*0.5+xpos, 1024+ypos-xpos*0.5);
		ObjSprite3D_SetSourceRect(StageBG2b, -wpos*0.5-xpos, ypos, 1024-wpos*0.5-xpos, 1024+ypos);
	}
}

task CreateSkyCloudsA1{
	loop(4){
		CreateCloudA1(200, BLEND_ALPHA, 0.75, 255, rand(0, 50), rand(450, 500), rand(256, 300), rand(0.25, 1.75), rand(-0.75, 0.15));
		CreateCloudA1(200, BLEND_ALPHA, 0.75, 255, rand(0, -50), rand(450, 500), rand(256, 300), rand(-0.25, -1.75), rand(-0.75, 0.15));
	}
	loop{
		CreateCloudA1(200, BLEND_ALPHA, 0.75, 255, rand(0, 50), rand(450, 500), rand(256, 300), rand(0.25, 1.75), rand(-0.75, 0.15));
		CreateCloudA1(200, BLEND_ALPHA, 0.75, 255, rand(0, -50), rand(450, 500), rand(256, 300), rand(-0.25, -1.75), rand(-0.75, 0.15));
		loop(30){yield};
	}
}

task CreateBrushGroupA1{
	loop(20){loop(2){CreateCloudA1(rand(70,128), BLEND_ADD_ARGB, 0.76, 128, rand(-200, 200), rand(100, 650), rand(32, 256), rand(-0.75, 0.75), rand(-0.75, 0.75));}}	
	CreateSkyCloudsA1;
	loop{
		loop(2){CreateCloudA1(rand(70,128), BLEND_ADD_ARGB, 0.76, 128, rand(-200, 200), rand(100, 650), rand(32, 256), rand(-0.75, 0.75), rand(-0.75, 0.75));}
		loop(12){yield};
	}
}
task CreateBrushGroupB1{
	ascent(i in 0..6){
		let randy = +rand(-48,48);
		CreateOnbashiraA1(1000/6*i+randy, 1, -112, -112);
		CreateOnbashiraA1(1000/6*i+randy, -1, -112, -112);
	}
	loop{
		CreateOnbashiraA1(0, 1, -112, -112);
		CreateOnbashiraA1(0, -1, -112, -112);
		loop(52){
			if(GetCommonData("Time.", false)){
				let nx = GetCommonData("Time.", 475);
				CreateOnbashiraA1(nx, 1, 500, -112);
				CreateOnbashiraA1(nx, -1, 500, -112);
				SetCommonData("Time.", 0);
			}
			yield
		};
	}
}

task CreateLeafA1{
	let leaf = Create3DBrush(255, 32, 0, stbg0, 0.23);
	ObjRender_SetZWrite(leaf, true);
	ObjRender_SetZTest(leaf, true);
	ObjSprite3D_SetDestRect(leaf, -16, -16, 16, 16);
	let locpos = [rand(-450, 450), rand(100,500), rand(128, 208)];
	let locang = [rand(0,360), rand(0,360), rand(0,360)];
	let locasp = [rand(-3, 3), rand(-3, 3), rand(-3, 3)];
	let alpha = 0;
	let etime = rand(60, 120);
	locpos[0] = locpos[0]-32;
	ObjRender_SetPosition(leaf, locpos[0], locpos[1], locpos[2]);
	ObjRender_SetAngleXYZ(leaf, locang[0], locang[1], locang[2]);
	ObjRender_SetScaleXYZ(leaf, 0.35, 0.35, 0.35);
	ObjRender_SetColor(leaf, 160, 192, 244);
	Obj_SetRenderPriority(leaf, 0.22);
	if(!GetCommonData("SelectionSet", false)){Obj_SetRenderPriority(leaf, 0.72);}
	
	while(etime > 0){
		etime--;
		alpha = min(alpha + 2, 128);
		UpdatePosition;
		yield;
	}
	while(alpha > 0){
		alpha = max(alpha - 2.5, 0);
		UpdatePosition;
		yield;
	}
	Obj_Delete(leaf);
	sub UpdatePosition{
		locpos[0]=locpos[0]-stgspeed/4;
		locpos[1]=locpos[1]-stgspeed/2;
		locpos[2]=locpos[2]-stgspeed/5;
		locang[0]=locang[0]+locasp[0];
		locang[1]=locang[1]+locasp[1];
		locang[2]=locang[2]+locasp[2];
		ObjRender_SetPosition(leaf, locpos[0], locpos[1], locpos[2]);
		ObjRender_SetAngleXYZ(leaf, locang[0], locang[1], locang[2]);
		ObjRender_SetAlpha(leaf, alpha);
	}
}

task CreateCloudA1(time, blend, pri, amax, x, y, z, xv, yv){
	let a = 0;
	let obj = Create3DBrush(255, 256, 0, stbg5, pri);
	ObjSprite3D_SetDestRect(obj, -128, -128, 128, 128);
	ObjRender_SetBlendType(obj, blend);
	ObjRender_SetPosition(obj, x, y, z);
	ObjRender_SetAngleXYZ(obj, 0, 0, rand(0,360));
	ObjRender_SetColor(obj, 160, 160, 208);
	if(blend == BLEND_ALPHA){
		ObjRender_SetColor(obj, 224, 224, 255);
	}
	ObjSprite3D_SetBillboard(obj, true);
	let mod2 = rand(0.5, 1.15);
	let IsSunIntersected = false;
	descent(i in 0..time){
		let mod = i/time;
		let scm = mod^0.25;
		a = min(a+0.5, amax);
		if(GetCommonData("SelectionSet", false)){Obj_SetRenderPriority(obj, pri-0.5);}
		x+=xv;
		y+=yv;
		z+=(xv+yv)*0.25;
		ObjRender_SetPosition(obj, x, y, z);
		ObjRender_SetScaleXYZ(obj, scm*mod2, scm*mod2, 1);
		ObjRender_SetAlpha(obj, a*mod^0.5);
		let d = GetObject2dPosition(obj);
		if(GetDistance(d[0]+64,d[1]+100,sun[0],sun[1])<144*scm){
			if(!IsSunIntersected){
				IsSunIntersected = true;
				if(blend == BLEND_ALPHA){gcount++;}else{gacount++;}
			}
		}else{
			if(IsSunIntersected&&blend == BLEND_ALPHA){
				IsSunIntersected = false;
				if(blend == BLEND_ALPHA){gcount--;}else{gacount--;}
			}
		}
		yield;
	}
	if(IsSunIntersected){if(blend == BLEND_ALPHA){gcount--;}else{gacount--;}}
	Obj_Delete(obj);
}

task CreateOnbashiraA1(beginbrush, side, z, destz){
	let obj = ObjMesh_Create();
	ObjMesh_Load(obj, source~"Pillar.mqo");
	let locpos = [136*side, 850, z];
	
	/*while(absolute(locpos[0]) < 96){ 
		locpos[0] = rand(-250, 250)
	}*/
	
	if(beginbrush){
		locpos[1] = beginbrush;
	}
	
	let fspeed = 10;
	
	ObjRender_SetPosition(obj, locpos[0], locpos[1], locpos[2]);
	ObjRender_SetAngleXYZ(obj, rand(0,360), 90, 90);
	ObjRender_SetScaleXYZ(obj, 1.25, 1.25, 1.35);
	Obj_SetRenderPriority(obj, 0.22);
	ObjRender_SetColor(obj, 96, 96, 144);
	let frame = round(rand(0, 140));
	
	
	if(locpos[2]>destz){
		locpos[0] = 80*side;
		while(locpos[2]>destz){
			fspeed = min(fspeed+0.2, 100);
			if(locpos[2]>destz){locpos[2]=max(locpos[2]-fspeed, -112);}
			locpos[1] = locpos[1] - stgspeed;
			ObjRender_SetPosition(obj, locpos[0], locpos[1], locpos[2]);
			yield;
		}
		PlaySoundA1("explode3");
		PlaySoundA1("rockpillar");
		PlaySoundA1("chargedown");
		PlaySoundA1("barrage");
		BackgroundShakeA1(16, 0.75);
		CreateRippleA1(locpos[0], locpos[1], -23, 110, 2.25);
		CreateRippleA1(locpos[0], locpos[1], -23, 130, 2);
		CreateRippleA1(locpos[0], locpos[1], -23, 140, 1.65);
		CreateRippleA1(locpos[0], locpos[1], -23, 120, 1.25);
		CreateRippleA1(locpos[0], locpos[1], -23, 70, 1);
		loop(8){CreateSplashA1(locpos[0]+rand(-32, 32), locpos[1]+rand(-48, 16));}
	}
	
	while(locpos[1]>-256){
		frame++;
		fspeed = min(fspeed+0.1, 40);
		if(locpos[2]>destz){locpos[2]=max(locpos[2]-fspeed, -112);}
		locpos[1] = locpos[1] - stgspeed;
		ObjRender_SetPosition(obj, locpos[0], locpos[1], locpos[2]);
		if(frame%10==0){
			CreateRippleA1(locpos[0], locpos[1], -23, 45, 0.5);
			if(frame>=90){
				CreateRippleA1(locpos[0], locpos[1], -23, 150, 1);
				frame = 0;
			}
		}
		
		yield;
	}
	Obj_Delete(obj);
}

task CreateRippleA1(x, y, z, time, scl){
	let obj = Create3DBrush(255, 400, 0, source~"water.png", 0.23);
	ObjSprite3D_SetDestRect(obj, -200, -200, 200, 200);
	ObjRender_SetBlendType(obj, BLEND_ADD_ARGB);
	ObjRender_SetPosition(obj, x, y, z);
	ObjRender_SetAngleXYZ(obj, 0, 0, 0);
	ObjRender_SetColor(obj, 48, 120, 192);
	Obj_SetRenderPriority(obj, 0.22);
	if(!GetCommonData("SelectionSet", false)){Obj_SetRenderPriority(obj, 0.72);}
	
	ascent(i in 0..time){
		let mod = i/time;
		let scm = scl*mod;
		y-=stgspeed;
		ObjRender_SetY(obj, y);
		ObjRender_SetScaleXYZ(obj, 0.05+scm, 0.05+scm, 1);
		ObjRender_SetAlpha(obj, 192-192*mod^0.5);
		yield;
	}
	Obj_Delete(obj);
}

task CreateSplashA1(x, y){
	let z = 12;
	y-=24;
	let obj = Create3DBrush(255, 256, 0, source~"water2.png", 0.23);
	ObjSprite3D_SetDestRect(obj, -64, -256, 64, 0);
	ObjRender_SetBlendType(obj, BLEND_ADD_ARGB);
	ObjRender_SetPosition(obj, x, y, z);
	ObjRender_SetAngleXYZ(obj, 0, 0, rand(-25, 25));
	let scl = [rand(0.5, 1.2),rand(0.5, 1.2)];
	ObjRender_SetScaleXYZ(obj, scl[0], scl[1], 1);
	ObjSprite3D_SetBillboard(obj, true);
	ObjRender_SetColor(obj, 48, 120, 192);
	Obj_SetRenderPriority(obj, 0.22);
	
	let time = round(rand(78, 140));
	let zx = 45;
	let alpha = rand(108, 160);
	let adec = rand(2.5, 3.75);
	
	while(alpha>0){
		zx+=3.5;
		z+=8*sin(min(270, zx));
		y-=stgspeed;
		alpha-=adec;
		scl+=[adec/200, adec/150];
		ObjRender_SetY(obj, y);
		ObjRender_SetZ(obj, z);
		ObjRender_SetScaleXYZ(obj, scl[0], scl[1], 1);
		ObjRender_SetAlpha(obj, alpha);
		yield;
	}
	Obj_Delete(obj);
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
	ObjRender_SetZWrite(StageProp, true);
	ObjRender_SetZTest(StageProp, true);
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
	let pos = [0,0,100];
	let ang = [90,295,300];
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
		
		SetCameraFocusX(pos[0]);
		SetCameraFocusY(pos[1]);
		SetCameraFocusZ(pos[2]);
		SetCameraAzimuthAngle(ang[0]);	
		SetCameraElevationAngle(ang[1]);
		SetCameraRadius(ang[2]);
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

