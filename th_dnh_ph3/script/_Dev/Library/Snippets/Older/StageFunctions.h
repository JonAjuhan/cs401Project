
#include"./SpellPracticeData.h"

let MainSTG = GetMainStgScriptDirectory;
let SpellSource = MainSTG~"source/Boss/";
let img_effect = MainSTG~"ds_system/img/effect.png"; // Effect Sheet
let img_frame = MainSTG~"ds_system/img/frame2.png"; // Effect Sheet

let ScriptNamesE = [];
let ScriptNamesN = [];
let ScriptNamesH = [];
let ScriptNamesL = [];
let ScriptNamesO = [];
let ScriptNamesC = [];
let ScriptIDs = [];

let sdiff = 36;
let dir = GetCurrentScriptDirectory;
let options = [85, 85, 2, 3, 2, 0];
let playerdefeated = 0;

function PlayMusic(str){
	let objSound = ObjSound_Create;
	ObjSound_SetSoundDivision(objSound, SOUND_BGM);
	ObjSound_SetLoopEnable(objSound, true);
	ObjSound_SetVolumeRate(objSound, 100);
	if(str=="magusnight"){
		LoadSound(MainSTG~"source/marisabgm.ogg");
		ObjSound_Load(objSound, MainSTG~"source/marisabgm.ogg");
		ObjSound_SetLoopTime(objSound, 0, 126);  //206 ?
		ObjSound_Play(objSound);
	}
	return objSound;
}


function DrawText(txtStr, txtX, txtY, txtSize, txtWidth, presetTxtColor, txtPriority){
	let SnowDrawText = ObjText_Create;
	ObjText_SetText(SnowDrawText,txtStr);
	SetTextColor;
	ObjText_SetFontSize(SnowDrawText,txtSize);
	ObjText_SetHorizontalAlignment(SnowDrawText, ALIGNMENT_LEFT);
	ObjText_SetFontBorderWidth(SnowDrawText,1);
	ObjText_SetFontBorderType(SnowDrawText,BORDER_FULL);
	ObjText_SetMaxWidth(SnowDrawText, txtWidth);
	Obj_SetRenderPriority(SnowDrawText, txtPriority);
	ObjRender_SetPosition(SnowDrawText, txtX, txtY, 0);
	
	SetTextColor;
	
	task SetTextColor{
		if(presetTxtColor=="black"){
			ObjText_SetFontColorTop(SnowDrawText,42,42,42);
			ObjText_SetFontColorBottom(SnowDrawText,42,42,42);
			ObjText_SetFontBorderColor(SnowDrawText,142,142,142);
		}
		if(presetTxtColor=="red"){
			ObjText_SetFontColorTop(SnowDrawText,175,20,111);
			ObjText_SetFontColorBottom(SnowDrawText,190,10,123);
			ObjText_SetFontBorderColor(SnowDrawText,142,142,142);
		}
		if(presetTxtColor=="blue"){
			ObjText_SetFontColorTop(SnowDrawText,20,80,175);
			ObjText_SetFontColorBottom(SnowDrawText,80,50,175);
			ObjText_SetFontBorderColor(SnowDrawText,142,142,142);
		}
		if(presetTxtColor=="white"){
			ObjText_SetFontColorTop(SnowDrawText,255,255,255);
			ObjText_SetFontColorBottom(SnowDrawText,185,185,185);
			ObjText_SetFontBorderColor(SnowDrawText,32,32,32);
		}
	}
	
	return SnowDrawText;
}

function CreateEnemyA1(enemytype, x, y, enmspd, enmang, life, fcolor, argument, argument2){
	let enemyscript;
	if(enemytype == "Enemy1"){enemyscript = LoadScript(dir ~ "Enemy01.txt");}
	if(enemytype == "Boss1"){enemyscript = LoadScript(dir ~ "SnowPlural.txt");}
	SetScriptArgument(enemyscript, 1, fcolor);
	SetScriptArgument(enemyscript, 2, x);
	SetScriptArgument(enemyscript, 3, y);
	SetScriptArgument(enemyscript, 4, enmspd);
	SetScriptArgument(enemyscript, 5, enmang);
	SetScriptArgument(enemyscript, 6, argument);
	SetScriptArgument(enemyscript, 7, argument2);
	SetScriptArgument(enemyscript, 8, life);
	StartScript(enemyscript);
	return enemyscript;
}

function Wait(waitframes){
	loop(waitframes){yield}
}

task PlaySound(name){
	let ID = -1;
	let GlobalSounds = GetCommonData("GlobalSoundData", [-1]);
	let GlobalSndStr = GetCommonData("GlobalSndStrData", [-1]);
	ascent(i in 0..length(GlobalSndStr)){
		if(GlobalSndStr[i]==name){ID = i; break;}
	}
	if(ID==-1){RaiseError("Error when attempting to play audio: "~name);}
	ObjSound_SetVolumeRate(GlobalSounds[ID], SE_VOL);
	ObjSound_Play(GlobalSounds[ID]);
}






task SelectionScreen{
	/*
	let menuscreen = ObjPrim_Create(OBJ_SPRITE_2D);
	let finalalpha = 255;
	ObjRender_SetBlendType(menuscreen, BLEND_ALPHA);
	Obj_SetRenderPriorityI(menuscreen, 74);
	
	while(SelectionSet!=2){
		yield;
	}
	
	SetCommonData("SelectionSet", 2);
	ObjPrim_SetTexture(menuscreen, MainSTG~"source/img_select2.png");
	ObjSprite2D_SetSourceRect(menuscreen, 0, 0, 12, 12);
	ObjSprite2D_SetDestRect(menuscreen, 0, 0, 416, 464);
	while(finalalpha>0){
		finalalpha-=255/35;
		ObjRender_SetAlpha(menuscreen, finalalpha);
		yield;
	}
	
	Obj_Delete(menuscreen);
	*/
}

task FallingLeafA1(deX, deY, colorR, colorG, colorB, deScale){
	
	let obj = ObjPrim_Create(OBJ_SPRITE_2D);
	let obj_time = 0;
	let angX = rand(-360, 360);
	let angY = rand(-360, 360);
	let angZ = rand(-360, 360);
	ObjRender_SetBlendType(obj, BLEND_ALPHA);
	Obj_SetRenderPriority(obj, 0.75);
	ObjPrim_SetTexture(obj, img_effect);
	ObjSprite2D_SetSourceRect(obj, 0, 228, 33, 251);
	ObjSprite2D_SetDestRect(obj, -16, -12, 16, 12);
	ObjRender_SetAngleXYZ(obj, angX, angY, angZ);
	ObjRender_SetPosition(obj, deX, deY, 0);
	ObjRender_SetColor(obj, colorR, colorG, colorB);
	ObjRender_SetAlpha(obj, 0);
	
	let alpha = 0;
	let scale = deScale;
	let randX = rand(50, 500);
	let randY = rand(50, 500);
	let RandZ = rand(17,170);
	//atan2(randY - deX, randX - deY);
	while(Obj_IsDeleted(obj)==false){
		obj_time++;
		
		if(obj_time<180 && alpha<105){alpha+=3}
		if(obj_time>180){alpha += -1;}
		alpha += 0.1;
		deX += randX/250;
		deY += randY/250;
		angX += randX/255;
		angY += randY/255;
		angZ += randX/295+randY/295;
		
		ObjRender_SetPosition(obj, deX, deY, 0);
		ObjRender_SetAngleXYZ(obj, angX, angY, angZ);
		ObjRender_SetAlpha(obj, alpha);
		ObjRender_SetScaleXYZ(obj, scale, scale, scale);
		
		if(alpha<0){Obj_Delete(obj)}
		yield;
	}
	Obj_Delete(obj);
}

task SetTextColor(objectID, presetTxtColor){
	if(presetTxtColor=="black"){
		ObjText_SetFontColorTop(objectID,42,42,42);
		ObjText_SetFontColorBottom(objectID,42,42,42);
		ObjText_SetFontBorderColor(objectID,142,142,142);
	}
	if(presetTxtColor=="red"){
		ObjText_SetFontColorTop(objectID,175,20,111);
		ObjText_SetFontColorBottom(objectID,190,10,123);
		ObjText_SetFontBorderColor(objectID,142,142,142);
	}
	if(presetTxtColor=="blue"){
		ObjText_SetFontColorTop(objectID,20,80,175);
		ObjText_SetFontColorBottom(objectID,80,50,175);
		ObjText_SetFontBorderColor(objectID,142,142,142);
	}
}

function SetStageDifficulty{
	yield;
	let selection = 2;
	let Instructions1;
	let Instructions2;
	
	let TextObjects = [];
	let TextNames = ["Easy", "Normal", "Hard", "Lunatic", "Overdrive", "Ultra"];
	
	let r = [96,  96,  96,  255, 255, 0  ];
	let g = [255, 208, 128, 96,  48,  255];
	let b = [128, 255, 255, 255, 48,  255];
	
	let diffs = [12, 36, 48, 72, 96, 120];
	let Cord = [GetStgFrameWidth/2-100, GetStgFrameHeight/2+100];
	let Center = [GetStgFrameWidth/2, GetStgFrameHeight/2];
	ascent(i in 0..length(TextNames)){
		TextObjects = TextObjects~[DrawSubMenuText(TextNames[i])];
		let locText = TextObjects[i];
		ObjText_SetHorizontalAlignment(locText, ALIGNMENT_CENTER);
		ObjRender_SetPosition(locText, Cord[0]-90, Cord[1]-150+i*25, 0);
		ObjText_SetMaxWidth(locText, 180);
		Obj_SetVisible(locText, true);
		ObjText_SetFontSize(locText,18);
		ObjText_SetFontBorderColor(locText,16,16,16);
	}
	
	let objMark = CreateSelectMarker;
	ObjRender_SetPosition(objMark, Cord[0], Cord[1]-150+selection*25, 0);
	loop{
		Cord[0] = min(Cord[0]+8, Center[0]);
		Cord[1] = max(Cord[1]-8, Center[1]);
		ObjRender_SetPosition(objMark, Cord[0], Cord[1]-150+10+selection*25, 0);
		if(GetVirtualKeyState(VK_UP)==KEY_PUSH){selection--;PlaySound("se_select00");}
		if(GetVirtualKeyState(VK_DOWN)==KEY_PUSH){selection++;PlaySound("se_select00");}
		if(selection<0){selection=5}
		if(selection>5){selection=0}
		
		ascent(i in 0..length(TextObjects)){
			ObjRender_SetPosition(TextObjects[i], Cord[0]-90, Cord[1]-150+i*25, 0);
			if(selection == i){
				ObjText_SetFontColorTop(TextObjects[i], r[i], g[i], b[i]);
				ObjText_SetFontColorBottom(TextObjects[i], r[i]/1.5, g[i]/1.5, b[i]/1.5);
			}else{
				ObjText_SetFontColorTop(TextObjects[i], r[i]/1.75, g[i]/1.75, b[i]/1.75);
				ObjText_SetFontColorBottom(TextObjects[i], r[i]/2.25, g[i]/2.25, b[i]/2.25);
			}
		}
		
		if(GetVirtualKeyState(VK_SHOT)==KEY_PUSH){
			sdiff = diffs[selection];
			SetCommonData("StageDiffic", sdiff);
			PlaySound("se_ok00");
			break;
		}
		/*if(GetVirtualKeyState(VK_BOMB)==KEY_PUSH){
			PlaySound("selectcancel");
			break;
		}*/
		yield;
	}
	ascent(i in 0..length(TextObjects)){
		Obj_Delete(TextObjects[i]);
	}
	Obj_Delete(objMark);
}

function SetStageQuality{
	yield;
	let selection = 2;
	let Instructions1;
	let Instructions2;
	
	let TextObjects = [];
	let TextNames = ["None", "Little", "Normal", "Very High"];
	
	let Cord = [GetStgFrameWidth/2, GetStgFrameHeight/2];
	ascent(i in 0..length(TextNames)){
		TextObjects = TextObjects~[DrawSubMenuText(TextNames[i])];
		let locText = TextObjects[i];
		ObjText_SetHorizontalAlignment(locText, ALIGNMENT_CENTER);
		ObjRender_SetPosition(locText, Cord[0]-90, Cord[1]-150+i*25, 0);
		ObjText_SetMaxWidth(locText, 180);
		Obj_SetVisible(locText, true);
		ObjText_SetFontSize(locText,18);
		ObjText_SetFontBorderColor(locText,16,16,16);
	}
	
	
	let Description = DrawText("", 42, Cord[1]+135, 18, 300, "white", 0.80);
	ObjText_SetHorizontalAlignment(Description, ALIGNMENT_CENTER);
	let objMark = CreateSelectMarker;
	ObjRender_SetPosition(objMark, Cord[0], Cord[1]-150+selection*25, 0);
	loop{
		ObjRender_SetPosition(objMark, Cord[0], Cord[1]-150+10+selection*25, 0);
		if(GetVirtualKeyState(VK_UP)==KEY_PUSH){selection--;PlaySound("se_select00");}
		if(GetVirtualKeyState(VK_DOWN)==KEY_PUSH){selection++;PlaySound("se_select00");}
		if(selection<0){selection=3}
		if(selection>3){selection=0}
		
		ascent(i in 0..length(TextObjects)){
			if(selection == i){
				ObjRender_SetColor(TextObjects[i], 255, 255, 255);
				alternative(selection)
				case(0){ObjText_SetText(Description,"Almost all effects removed.[r]Minimal effects used for key notifications.");}
				case(1){ObjText_SetText(Description,"Many effects reduced. Lifebar[r]is changed into a bar.");}
				case(2){ObjText_SetText(Description,"Default quality. Every effect is left as was intended.");}
				case(3){ObjText_SetText(Description,"Some effects are added that[r]may cause notable lag.");}
				others{ObjText_SetText(Description,"Error: Invalid Selection");}
			}else{
				ObjRender_SetColor(TextObjects[i], 128, 128, 128);
			}
		}
		
		if(GetVirtualKeyState(VK_SHOT)==KEY_PUSH){
			SetCommonData("quality", selection);
			PlaySound("se_ok00");
			break;
		}
		/*if(GetVirtualKeyState(VK_BOMB)==KEY_PUSH){
			PlaySound("selectcancel");
			break;
		}*/
		yield;
	}
	ascent(i in 0..length(TextObjects)){
		Obj_Delete(TextObjects[i]);
	}
	Obj_Delete(Description);
	Obj_Delete(objMark);
	SetCommonData("SelectionSet", true);
}

function SetOptionsMenu{
	yield;
	let selection = 0;
	let selecthold = -16;
	let selectinc = 0;
	let selectlife = [0, 0];
	let locked = false;
	let Cord = [176, GetStgFrameHeight/1.5];
	
	let TextObjects = [];
	let QualObjects = [];
	let InviObjects = [];
	let LifeObjects = [ID_INVALID, ID_INVALID];
	let BombObjects = [ID_INVALID, ID_INVALID];
		LifeObjects[0] = DrawSubMenuText("Default");
		ObjRender_SetPosition(LifeObjects[0], Cord[0]+112, Cord[1]-45, 0);
		SetDefaultTextProp(LifeObjects[0]);
		
		LifeObjects[1] = DrawSubMenuText("<< "~rtos("00", options[3])~" >>");
		ObjRender_SetPosition(LifeObjects[1], Cord[1]+112, Cord[1]-45, 0);
		SetDefaultTextProp(LifeObjects[1]);
		
		BombObjects[0] = DrawSubMenuText("Default");
		ObjRender_SetPosition(BombObjects[0], Cord[0]+112, Cord[1]-10, 0);
		SetDefaultTextProp(BombObjects[0]);
		
		BombObjects[1] = DrawSubMenuText("<< "~rtos("00", options[4])~" >>");
		ObjRender_SetPosition(BombObjects[1], Cord[1]+112, Cord[1]-10, 0);
		SetDefaultTextProp(BombObjects[1]);
		
	let TextNames = ["Volume BGM", "Volume SE", "Effects Quality", "Set Lives", "Set Bombs", "Invinicbility Time", "Return To Main Menu"];
	let QualText = ["None", "Low", "Normal", "High"];
	let InviText = ["Normal", "Extend", "Always"];
	ascent(i in 0..length(TextNames)){
		TextObjects = TextObjects~[DrawSubMenuText(TextNames[i])];
		let locText = TextObjects[i];
		ObjRender_SetPosition(locText, Cord[0]-90, Cord[1]-150+i*35, 0);
		SetDefaultTextProp(locText);
	}
	ascent(i in 0..length(QualText)){
		QualObjects = QualObjects~[DrawSubMenuText(QualText[i])];
		let locText = QualObjects[i];
		ObjRender_SetPosition(locText, Cord[0]+112+64*i, Cord[1]-80, 0);
		if(i == 2){ObjRender_SetPosition(locText, Cord[0]+112+57*i, Cord[1]-80, 0);}
		SetDefaultTextProp(locText);
	}
	ascent(i in 0..length(InviText)){
		InviObjects = InviObjects~[DrawSubMenuText(InviText[i])];
		let locText = InviObjects[i];
		ObjRender_SetPosition(locText, Cord[0]+112+80*i, Cord[1]+25, 0);
		SetDefaultTextProp(locText);
	}
	
	let BGM_bg = CreateBar;
	ObjRender_SetPosition(BGM_bg, Cord[0]+112, Cord[1]-140, 0);
	ObjRender_SetColor(BGM_bg, 64, 64, 64);
	let BGM = CreateBar;
	ObjRender_SetPosition(BGM, Cord[0]+112, Cord[1]-140, 0);
	ObjRender_SetColor(BGM, 112, 112, 112);
	let SE_bg = CreateBar;
	ObjRender_SetPosition(SE_bg, Cord[0]+112, Cord[1]-105, 0);
	ObjRender_SetColor(SE_bg, 64, 64, 64);
	let SE = CreateBar;
	ObjRender_SetPosition(SE, Cord[0]+112, Cord[1]-105, 0);
	ObjRender_SetColor(SE, 112, 112, 112);
	
	loop{
		if(GetVirtualKeyState(VK_UP)==KEY_PUSH&&!locked){selection--;PlaySound("se_select00");}
		if(GetVirtualKeyState(VK_DOWN)==KEY_PUSH&&!locked){selection++;PlaySound("se_select00");}
		if(selection<0){selection=6}
		if(selection>6){selection=0}
		
		if(GetVirtualKeyState(VK_SHOT)==KEY_PUSH&&!locked){
			PlaySound("se_select00");
			if(selection == 6){break;}
		}
		if(GetVirtualKeyState(VK_BOMB)==KEY_PUSH&&!locked){
			PlaySound("se_cancel00");
			if(selection == 6){break;}
			selection = 6;
		}
		
		ObjRender_SetColor(BGM, 112, 112, 112);
		ObjSprite2D_SetDestRect(BGM, 0, -4, (256/100)*options[0], 4);
		ObjRender_SetColor(SE, 112, 112, 112);
		ObjSprite2D_SetDestRect(SE, 0, -4, (256/100)*options[1], 4);
		
		alternative(selection)
		case(0){VolumeControl(0);ObjRender_SetColor(BGM, 224, 224, 224);}
		case(1){VolumeControl(1);ObjRender_SetColor(SE, 224, 224, 224);}
		case(2){QualityControl;}
		case(3){LifeBombControl(0);}
		case(4){LifeBombControl(1);}
		case(5){InvincibilityControl;}
		
		ascent(i in 0..length(TextObjects)){
			if(selection == i){
				ObjRender_SetColor(TextObjects[i], 255, 255, 255);
			}else{
				ObjRender_SetColor(TextObjects[i], 128, 128, 128);
			}
		}
		ascent(i in 0..length(QualObjects)){
			let active = 1.5;
			if(selection == 2){active = 1;}
			if(options[2] == i){
				ObjRender_SetColor(QualObjects[i], 255/active, 255/active, 255/active);
			}else{
				ObjRender_SetColor(QualObjects[i], 128/active, 128/active, 128/active);
			}
		}
		ascent(i in 0..length(LifeObjects)){
			let active = 1.5;
			if(selection == 3){active = 1;}
			if(selectlife[0] == i){
				ObjRender_SetColor(LifeObjects[i], 255/active, 255/active, 255/active);
			}else{
				ObjRender_SetColor(LifeObjects[i], 128/active, 128/active, 128/active);
			}
		}
		ascent(i in 0..length(BombObjects)){
			let active = 1.5;
			if(selection == 4){active = 1;}
			if(selectlife[1] == i){
				ObjRender_SetColor(BombObjects[i], 255/active, 255/active, 255/active);
			}else{
				ObjRender_SetColor(BombObjects[i], 128/active, 128/active, 128/active);
			}
		}
		ascent(i in 0..length(InviObjects)){
			let active = 1.5;
			if(selection == 5){active = 1;}
			if(options[5] == i){
				ObjRender_SetColor(InviObjects[i], 255/active, 255/active, 255/active);
			}else{
				ObjRender_SetColor(InviObjects[i], 128/active, 128/active, 128/active);
			}
		}
		yield;
	}
	
	SetCommonData("quality", options[2]);
	ascent(i in 0..length(TextObjects)){Obj_Delete(TextObjects[i]);}
	ascent(i in 0..length(QualObjects)){Obj_Delete(QualObjects[i]);}
	ascent(i in 0..length(LifeObjects)){Obj_Delete(LifeObjects[i]);}
	ascent(i in 0..length(BombObjects)){Obj_Delete(BombObjects[i]);}
	ascent(i in 0..length(InviObjects)){Obj_Delete(InviObjects[i]);}
	Obj_Delete(BGM);
	Obj_Delete(SE);
	Obj_Delete(BGM_bg);
	Obj_Delete(SE_bg);
	
	SetAreaCommonData("OptionConfig", "Options", options);
	SaveCommonDataAreaA1("OptionConfig");
	
	function SetDefaultTextProp(id){
		ObjText_SetMaxWidth(id, 300);
		Obj_SetVisible(id, true);
		ObjText_SetFontSize(id,16);
		ObjText_SetFontBorderColor(id,16,16,16);
	}
	
	function VolumeControl(num){
		if(IsAllKeysFree){selecthold = -16}
		if(GetVirtualKeyState(VK_RIGHT)==KEY_FREE){
			if(GetVirtualKeyState(VK_LEFT)==KEY_PUSH||selecthold>4){
				selecthold = 0;
				if(options[num]>0&&options[num]<100){PlaySound("se_select00");}
				if(num == 0){options[num] = max(options[num]-1-selectinc, 0);}
				if(num == 1){options[num] = max(options[num]-1-selectinc, 0);}
			}
			if(GetVirtualKeyState(VK_LEFT)==KEY_HOLD){
				selecthold++;
				selectinc+=0.025;
			}else{selecthold = -16;selectinc = 0;}
		}else{
			if(GetVirtualKeyState(VK_RIGHT)==KEY_PUSH||selecthold>4){
				selecthold = 0;
				if(options[num]>0&&options[num]<100){PlaySound("se_select00");}
				if(num == 0){options[num] = min(options[num]+1+selectinc, 100);}
				if(num == 1){options[num] = min(options[num]+1+selectinc, 100);}
			}
			if(GetVirtualKeyState(VK_RIGHT)==KEY_HOLD){
				selecthold++;
				selectinc+=0.025;
			}else{selecthold = -16;selectinc = 0;}
		}
	}
	function QualityControl{
		if(GetVirtualKeyState(VK_RIGHT)==KEY_PUSH){options[2]=options[2]+1;PlaySound("se_select00");}
		if(GetVirtualKeyState(VK_LEFT)==KEY_PUSH){options[2]=options[2]-1;PlaySound("se_select00");}
		if(options[2]>3){options[2] = 0;}
		if(options[2]<0){options[2] = 3;}
	}
	function InvincibilityControl{
		if(GetVirtualKeyState(VK_RIGHT)==KEY_PUSH){options[5]=options[5]+1;PlaySound("se_select00");}
		if(GetVirtualKeyState(VK_LEFT)==KEY_PUSH){options[5]=options[5]-1;PlaySound("se_select00");}
		if(options[5]>2){options[5] = 0;}
		if(options[5]<0){options[5] = 2;}
	}
	function LifeBombControl(num){
		if(GetVirtualKeyState(VK_SHOT)==KEY_PUSH&&selectlife[num]==1){
			PlaySound("se_ok00");
			if(!locked){locked = true;}else{locked = false}
		}
		if(GetVirtualKeyState(VK_SPELL)==KEY_PUSH&&locked){
			PlaySound("se_cancel00");
			selectlife[num] = 0;
			locked = false;
		}
		if(num==0){ObjText_SetText(LifeObjects[1],"<< "~rtos("00", options[num+3])~" >>");}
		if(num==1){ObjText_SetText(BombObjects[1],"<< "~rtos("00", options[num+3])~" >>");}
		if(!locked){
			if(GetVirtualKeyState(VK_RIGHT)==KEY_PUSH){selectlife[num]=selectlife[num]+1;PlaySound("se_select00");}
			if(GetVirtualKeyState(VK_LEFT)==KEY_PUSH){selectlife[num]=selectlife[num]-1;PlaySound("se_select00");}
			if(selectlife[num]>1){selectlife[num] = 0;}
			if(selectlife[num]<0){selectlife[num] = 1;}
		}else{
			if(num==0){ObjText_SetText(LifeObjects[1],"<--  "~rtos("00", options[num+3])~"  -->");}
			if(num==1){ObjText_SetText(BombObjects[1],"<--  "~rtos("00", options[num+3])~"  -->");}
			if(IsAllKeysFree){selecthold = -16}
			if(GetVirtualKeyState(VK_RIGHT)==KEY_FREE){
				if(GetVirtualKeyState(VK_LEFT)==KEY_PUSH||selecthold>4){
					selecthold = 0;
					if(options[num+3]>0&&options[num+3]<100){PlaySound("se_select00");}
					if(num == 0){options[num+3] = max(options[num+3]-1-selectinc, 0);}
					if(num == 1){options[num+3] = max(options[num+3]-1-selectinc, 0);}
				}
				if(GetVirtualKeyState(VK_LEFT)==KEY_HOLD){
					selecthold++;
					selectinc+=0.025;
				}else{selecthold = -16;selectinc = 0;}
			}else{
				if(GetVirtualKeyState(VK_RIGHT)==KEY_PUSH||selecthold>4){
					selecthold = 0;
					if(options[num]>0&&options[num+3]<99){PlaySound("se_select00");}
					if(num == 0){options[num+3] = min(options[num+3]+1+selectinc, 99);}
					if(num == 1){options[num+3] = min(options[num+3]+1+selectinc, 99);}
				}
				if(GetVirtualKeyState(VK_RIGHT)==KEY_HOLD){
					selecthold++;
					selectinc+=0.025;
				}else{selecthold = -16;selectinc = 0;}
			}
		}
	}
	
	
	function CreateBar{
		let obj = ObjPrim_Create(OBJ_SPRITE_2D);
		ObjRender_SetBlendType(obj, BLEND_ALPHA);
		Obj_SetRenderPriority(obj, 0.75);
		ObjPrim_SetTexture(obj, NULL);
		ObjSprite2D_SetSourceRect(obj, 0, 0, 1, 1);
		ObjSprite2D_SetDestRect(obj, 0, -4, 256, 4);
		return obj;
	}
}



function CreateCustomPlural{
	yield;
	let selection = 0;
	let menuselect = 0; //For the scroll effect
	let selecthold = [0, 0]; //for the hold scrolling effects
	let pdiff = 1; // The local version of sdiff
	//----
	let DiffNames = ["Easy", "Normal", "Hard", "Lunatic", "Overdrive", "Cirno"];
	//----
	
	let TextObjects = [];
	let TextAlphas = [];
	let Cord = [GetStgFrameWidth/2-300, GetStgFrameHeight/2];
	
	SetSpellNames;
	
	ascent(i in 0..length(ScriptNamesN)){
		TextObjects = TextObjects~[DrawSubMenuText(ScriptNamesN[i])];
		TextAlphas = TextAlphas~[0];
	}
	
	let FinalBuild = [];
	let CurBuildNum = [];
	let ArrayCount = 0;
	
	
	let StartGame = DrawSubMenuText("Return To Main Menu");
	ObjRender_SetPosition(StartGame, Cord[0], Cord[1]-48, 0);
	Obj_SetVisible(StartGame, true);
	ObjText_SetFontSize(StartGame,16);
	ObjText_SetFontBorderColor(StartGame,24,24,24);
	
	let BuildText = DrawSubMenuText("Current Attack IDs:");
	ObjText_SetHorizontalAlignment(BuildText, ALIGNMENT_CENTER);
	ObjRender_SetPosition(BuildText, Cord[0]+100, Cord[1]-128, 0);
	ObjText_SetMaxWidth(BuildText, 320);
	Obj_SetVisible(BuildText, true);
	ObjText_SetFontSize(BuildText,14);
	
	let BuildNumText = DrawSubMenuText("{None}");
	ObjText_SetHorizontalAlignment(BuildNumText, ALIGNMENT_CENTER);
	ObjRender_SetPosition(BuildNumText, Cord[0]+100, Cord[1]-112, 0);
	ObjText_SetMaxWidth(BuildNumText, 320);
	Obj_SetVisible(BuildNumText, true);
	ObjText_SetFontSize(BuildNumText,12);
	
	let DifficultyText = DrawSubMenuText(DiffNames[1]);
	let DiffAlpha = 0;
	ObjText_SetHorizontalAlignment(DifficultyText, ALIGNMENT_CENTER);
	ObjRender_SetPosition(DifficultyText, Cord[0]+256, Cord[1]-64, 0);
	ObjText_SetMaxWidth(DifficultyText, 120);
	Obj_SetVisible(DifficultyText, true);
	ObjText_SetFontSize(DifficultyText,24);

	loop{
		if(ArrayCount>0){
			ObjText_SetText(StartGame,"Start Game");
			let bts = "";
			ascent(i in 0..length(CurBuildNum)){
				bts = bts~CurBuildNum[i];
				if(i != length(CurBuildNum)-1){
					bts = bts ~ ", ";
				}
			}
			ObjText_SetText(BuildNumText,bts);
		}else{
			ObjText_SetText(StartGame,"Return To Main Menu");
			ObjText_SetText(BuildNumText,"{None}");
		}
		ascent(i in 0..length(TextObjects)){
			ObjRender_SetAlpha(TextObjects[i], TextAlphas[i]);
			TextAlphas[i] = min(TextAlphas[i]+10, 255);
			ObjRender_SetPosition(TextObjects[i], Cord[0], Cord[1]+(i-menuselect)*12, 0);
			Obj_SetVisible(TextObjects[i], true);
			if(selection == i){
				ObjRender_SetColor(TextObjects[i], 255, 255, 255);
			}else{
				ObjRender_SetColor(TextObjects[i], 128, 128, 128);
				if(i-menuselect<0||i-menuselect>15){
					Obj_SetVisible(TextObjects[i], false);
				}
			}
		}
		ObjRender_SetAlpha(DifficultyText, DiffAlpha);
		DiffAlpha = min(DiffAlpha+10, 255);
		
		
		if(selection==-1){
			ObjRender_SetColor(StartGame, 255, 255, 255);
		}else{
			ObjRender_SetColor(StartGame, 128, 128, 128);
		}
		
		
		if(GetVirtualKeyState(VK_UP)!=KEY_FREE&&GetVirtualKeyState(VK_DOWN)==KEY_FREE){
			selecthold[0] = selecthold[0]-1;
		}
		if(GetVirtualKeyState(VK_DOWN)!=KEY_FREE){
			selecthold[1] = selecthold[1]+1;
		}
		
		if((GetVirtualKeyState(VK_UP)==KEY_PUSH||selecthold[0] < -4)&&GetVirtualKeyState(VK_DOWN)==KEY_FREE){
			selection--;
			selecthold[0] = 0;
			selecthold[1] = 0;
			PlaySound("se_select00");
			if(selection-menuselect<0&&menuselect>0){
				menuselect--;
			}
			if(selection<-1){
				selection = length(TextObjects)-1;
				menuselect = length(TextObjects)-16;
			}
		}
		if((GetVirtualKeyState(VK_DOWN)==KEY_PUSH||selecthold[1] > 4)){
			selection++;
			selecthold[0] = 0;
			selecthold[1] = 0;
			PlaySound("se_select00");
			if(selection>length(TextObjects)-1){
				selection = -1;
				menuselect = 0;
			}
			if(selection-menuselect>15){
				menuselect++;
			}
		}
		if(GetVirtualKeyState(VK_UP)==KEY_PUSH){
			selecthold[0] = 16;
		}
		if(GetVirtualKeyState(VK_DOWN)==KEY_PUSH){
			selecthold[1] = -16;
		}
		if(GetVirtualKeyState(VK_LEFT)==KEY_PUSH){
			pdiff--;
			if(pdiff < 0){pdiff = 5;}
			ChangeDiff;
		}
		if(GetVirtualKeyState(VK_RIGHT)==KEY_PUSH){
			pdiff++;
			if(pdiff > 5){pdiff = 0;}
			ChangeDiff;
		}
		
		if(GetVirtualKeyState(VK_SHOT)==KEY_PUSH){
			if(selection == -1){
				break;
			}
			FinalBuild = FinalBuild~[ScriptIDs[selection]];
			CurBuildNum = CurBuildNum~[rtos("000", selection+1)];
			ArrayCount++;
			PlaySound("se_ok00");
		}
		if(GetVirtualKeyState(VK_SPELL)==KEY_PUSH){
			if(selection==-1){
				if(ArrayCount<=0){
					break;
				}
				ArrayCount--;
				FinalBuild = erase(FinalBuild, length(FinalBuild)-1);
				CurBuildNum = erase(CurBuildNum, length(CurBuildNum)-1);
			}
			selection = -1;
			menuselect = 0;
			PlaySound("se_cancel00");
		}
		yield;
	}
	ascent(i in 0..length(ScriptNamesE)){
		Obj_Delete(TextObjects[i]);
	}
	Obj_Delete(StartGame);
	Obj_Delete(BuildText);
	Obj_Delete(BuildNumText);
	Obj_Delete(DifficultyText);
	
	ScriptNamesE = [];
	ScriptNamesN = [];
	ScriptNamesH = [];
	ScriptNamesL = [];
	ScriptNamesO = [];
	ScriptNamesC = [];
	ScriptIDs = [];
	
	function ChangeDiff{
			FinalBuild = [];
			CurBuildNum = [];
			ArrayCount = 0;
			PlaySound("se_ok00");
			RedrawText;
	}

	if(length(FinalBuild)>0){
		PlaySound("se_ok00");
		SetCommonData("ScriptBuilderData", FinalBuild);
		return FinalBuild;
	}else{
		PlaySound("se_cancel00");
		return [""];
	}
	
	task RedrawText{
		DiffAlpha = 0;
		ascent(i in 0..length(TextAlphas)){
			TextAlphas[i] = 0;
		}
		yield;
		ObjText_SetText(DifficultyText,DiffNames[pdiff]);
		alternative(pdiff)
		case(0){ascent(i in 0..length(TextObjects)){ObjText_SetText(TextObjects[i],ScriptNamesE[i]);}}
		case(1){ascent(i in 0..length(TextObjects)){ObjText_SetText(TextObjects[i],ScriptNamesN[i]);}}
		case(2){ascent(i in 0..length(TextObjects)){ObjText_SetText(TextObjects[i],ScriptNamesH[i]);}}
		case(3){ascent(i in 0..length(TextObjects)){ObjText_SetText(TextObjects[i],ScriptNamesL[i]);}}
		case(4){ascent(i in 0..length(TextObjects)){ObjText_SetText(TextObjects[i],ScriptNamesO[i]);}}
		case(5){ascent(i in 0..length(TextObjects)){ObjText_SetText(TextObjects[i],ScriptNamesC[i]);}}
	}
}

	
function CreateSpellChoice(owner, path, name, comment){
	let id = length(ScriptIDs)+1;
	ScriptNamesE = ScriptNamesE ~ [rtos("000", id)~" - "~owner~"~"~name[0]];
	ScriptNamesN = ScriptNamesN ~ [rtos("000", id)~" - "~owner~"~"~name[1]];
	ScriptNamesH = ScriptNamesH ~ [rtos("000", id)~" - "~owner~"~"~name[2]];
	ScriptNamesL = ScriptNamesL ~ [rtos("000", id)~" - "~owner~"~"~name[3]];
	ScriptNamesO = ScriptNamesO ~ [rtos("000", id)~" - "~owner~"~"~name[4]];
	ScriptNamesC = ScriptNamesC ~ [rtos("000", id)~" - "~owner~"~"~name[5]];
	ScriptIDs = ScriptIDs~[path];
}

function DrawSubMenuText(txtStr){
	let objTxt = ObjText_Create;
	ObjText_SetText(objTxt,txtStr);
	ObjText_SetFontSize(objTxt,12);
	ObjText_SetFontColorTop(objTxt,255,255,255);
	ObjText_SetFontColorBottom(objTxt,255,255,255);
	ObjText_SetFontBorderType(objTxt,BORDER_FULL);
	ObjText_SetFontBorderColor(objTxt,48,48,48);
	ObjText_SetFontBorderWidth(objTxt,1);
	ObjText_SetHorizontalAlignment(objTxt, ALIGNMENT_LEFT);
	ObjText_SetMaxWidth(objTxt, 900);
	Obj_SetRenderPriority(objTxt, 0.75);
	return objTxt;
}

function CreateSelectMarker{
	let obj = ObjPrim_Create(OBJ_SPRITE_2D);
	ObjRender_SetBlendType(obj, BLEND_ALPHA);
	Obj_SetRenderPriority(obj, 0.74);
	ObjPrim_SetTexture(obj, img_frame);
	ObjSprite2D_SetSourceRect(obj, 48, 416, 176, 464);
	ObjSprite2D_SetDestRect(obj, -64, -16, 64, 16);
	return obj;
}

function IsAllKeysFree{
	return GetVirtualKeyState(VK_LEFT) == KEY_FREE &&
	GetVirtualKeyState(VK_RIGHT) == KEY_FREE &&
	GetVirtualKeyState(VK_UP) == KEY_FREE &&
	GetVirtualKeyState(VK_DOWN) == KEY_FREE;
}


//dumb local{} not working at the top
