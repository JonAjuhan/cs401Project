VERY FEW OF THESE GRAPHICS BELONG TO ME.
IF A GRAPHIC DOES NOT BELONG TO ME, IT BELONGS TO ITS RESPECTIVE OWNER.
THANK YOU. ~

Thank you for using my code!
I'm still a beginner in scripting, so feedback is greatly appriciated.

All you need to do is include "GizmoSpriteLibrary.txt" for bosses
or "GizmoFSpriteLibrary.txt" for fairies, and you're ready to go!

You are welcome to remove any functions that you will not be using in
your scripts. This library is pretty big.

Use any of the functions below to render the respective sprite onto
"obj". From there, if the sprite has a cast animation, use
"Obj_SetValue(obj,"cast",num);" anywhere in the script to
activate the character's cast animation. Atempting to activate a
cast animation on a sprite that does not have one will break the
sprite.
/---------------------------------/
"Obj_SetValue(obj,"cast",num);"
num = 0, Regular animation.
num = 1, Charge/Activate cast animation. You'll have to set the ObjValue to 0 again to return to normal animation.
num = 2, If the animation is chargeable, it activates the cast animation, or plays the whole cast animation all together.
/---------------------------------/



Available sprites and their functions:

TOUHOU CANON
~~~~~~~~~~~~

Reimu from IN: renderReimuIN(obj,type);
type = 1, Regular Reimu
type = 2, Blue Reimu (PoFV)
type = 3, Mamizou'd Reimu (TD)

Marisa from IN: renderMarisaIN(obj,type);
type = 1, Regular Marisa
type = 2, Dark Purple Marisa (PoFV)

Sakuya from PoFV: renderSakuyaPoFV(obj,type);
(No Cast Animation)
type = 1, Regular Sakuya
type = 2, Slightly Grayer Sakuya

Youmu from PoFV: renderYoumuPoFV(obj);
(Chargable Cast Animation)

Cirno from PoFV: renderCirnoPoFV(obj,type);
(No Cast Animation)
type = 1, Regular Cirno
type = 2, Black Cirno

Lyrica from PoFV: renderLyricaPoFV(obj,type);
type = 1, Regular Lyrica
type = 2, Yellow Lyrica

Merlin from PoFV: renderMerlinPoFV(obj,type);
type = 1, Regular Merlin
type = 2, Greenish Merlin

Lunasa from PoFV: renderLunasaPoFV(obj,type);
type = 1, Regular Lunasa
type = 2, All-Black Lunasa

Mystia from IN: renderMystiaIN(obj,type);
type = 1, Regular Mystia
type = 2, Green-Blue Mystia (PoFV)

Tewi from IN: renderTewiIN(obj,type);
(No Cast Animation)
type = 1, Regular Tewi
type = 2, Black Tewi (PoFV)

Yuuka from PoFV: renderYuukaPoFV(obj,type);
type = 1, Regular Yuuka
type = 2, Blue Yuuka

Aya from PoFV: renderAyaPoFV(obj,type);
(No Cast Animation)
type = 1, Regular Aya
type = 2, Blue-White Aya

Medicine from PoFV: renderMedicinePoFV(obj,type);
(No Cast Animation)
type = 1, Regular Medicine
type = 2, Purple Medicine

Wriggle from IN: renderWriggleIN(obj);

Shikieiki from PoFV: renderEikiPoFV(obj,type);
type = 1, Regular Eiki
type = 2, Purple-ish Eiki

Komachi from PoFV: renderKomachiPoFV(obj,type);
(Chargable Cast Animation)
type = 1, Regular Komachi
type = 2, Green Komachi

Keine from IN: renderKeineIN(obj,type);
type = 1, Regular Keine
type = 2, Beast Keine

Reisen from IN: renderReisenIN(obj);
(No Cast Animation)

Eirin from IN: renderEirinIN(obj);

Kaguya from IN: renderKaguyaIN(obj);
(No Cast Animation)

Mokou from IN: renderMokouIN(obj);

Shizuha from MoF: renderShizuhaMoF(obj);
(No Cast Animation)

Minoriko from MoF: renderMinorikoMoF(obj);

Hina from MoF: renderHinaMoF(obj);
(Both her cast animation and her moving animation are her spinning frames. Keep this in mind.)
(Obj_Value "cast" set to 1 is normal spinning. Set it to 2 to go to LIGHT SPEED!)

Nitori from DS: renderNitoriDS(obj,type);
type = 1, Regular Nitori
type = 2, Water-Camo Nitori (MoF)
(Type 2 does not have a cast animtion. Attemping to activate it will turn her invisible.)

Aya from DS: renderAyaDS(obj);
(Chargable Cast Animation)

Momiji from DS: renderMomijiDS(obj);
(Chargable Cast Animation)

Sanae from MoF: renderSanaeMoF(obj);

Kanako from MoF: renderKanakoMoF(obj,type);
(Chargable Cast Animation)
type = 1, Regular Kanako
type = 2, Invincible Kanako

Suwako from MoF: renderSuwakoMoF(obj,type);
(Chargable Cast Animation)
type = 1, Regular Suwako
type = 2, Invincible Suwako

Kisume from SA: renderKisumeSA(obj);
(No Cast Animation)

Yamame from SA: renderYamameSA(obj);

Parsee from SA: renderParseeSA(obj);

Yuugi from SA: renderYuugiSA(obj);

Satori from SA: renderSatoriSA(obj);
(No Cast Animation)

Mysterious Cat from SA: renderCatSA(obj);
(No Cast Animation)

Orin from SA: renderOrinSA(obj);

Utsuho from SA: renderUtsuhoSA(obj);

Koishi from SA: renderKoishiSA(obj);

Nazrin from UFO: renderNazrinUFO(obj);

Kogasa from UFO: renderKogasaUFO(obj);

Ichirin from UFO: renderIchirinUFO(obj);

Murasa from UFO: renderMurasaUFO(obj);
This sprite is special. Murasa's normal and phantom forms are
interchangable at any time during the script and can be
switched with the Obj_Value "phan". Setting it to 1 will
activate her phantom form, and 0 turns her back to normal.

Shou from UFO: renderShouUFO(obj);

Byakuren from UFO: renderByakurenUFO(obj);

Nue from UFO: renderNueUFO(obj);

Yuyuko from TD: renderYuyukoTD(obj);

Kyouko from TD: renderKyoukoTD(obj);

Yoshika from TD: renderYoshikaTD(obj);

Seiga from TD: renderSeigaTD(obj);

Tojiko from TD: renderTojikoTD(obj);
(No Cast Animation)

Futo from TD: renderFutoTD(obj);

Miko from TD: renderMikoTD(obj);
(Chargable Cast Animation)

Mamizou from TD: renderMamizouTD(obj);

Tenshi from DS: renderTenshiDS(obj);
(Chargable Cast Animation)

Iku from DS: renderIku(obj);
(Chargable Cast Animation)

Hatate from DS: renderHatateDS(obj);
(Chargable Cast Animation)

Luna from GFW: renderLunaGFW(obj);

Star from GFW: renderStarGFW(obj);

Sunny from GFW: renderSunnyGFW(obj);

Marisa from GFW: renderMarisaGFW(obj);

Daiyousei from GFW: renderDaiyouseiGFW(obj);
(No Cast Animation)

Lily White/Black from GFW: renderLilyGFW(obj,type);
type = 1, Lily White
type = 2, Lily Black

Cirno from DDC: renderCirnoDDC(obj);

Wakasagihime from DDC: renderWakasagihimeDDC(obj);
This sprite also uses the "phan" ObjValue. It can be changed at any time (in theory. This hasn't been tested).
Another thing to note is that the sprite strangely starts out flipped vertically.

Sekibanki from DDC: renderSekibankiDDC(obj);
Again, this sprite uses the "phan" ObjValue. Setting it to 1
will make her appear headless.

Kagerou from DDC: renderKagerou(obj);
(No wolf-missile animation during casting. Sorry. She does spin, though.)

Benben from DDC: renderBenbenDDC(obj);
(No Cast Animation)

Yatsuhashi from DDC: renderYatsuhashiDDC(obj);

Seija from DDC: renderSeijaDDC(obj);

Shinmyoumaru from DDC: renderShinmyoumaruDDC(obj);

Raiko from DDC: renderRaikoDDC(obj);
(Chargable Cast Animation)

Seiran from LoLK: renderSeiranLoLK(obj);

Ringo from LoLK: renderRingoLoLK(obj);

Doremy from LoLK: renderDoremyLoLK(obj);

Sagume from LoLK: renderSagumeLoLK(obj);
Setting the Obj_Value "cast" to 1 will automatically
set it back to 0 when the animation is finished.


FAIRIES AND OTHER ENEMIES  (None of these have cast animations.)
~~~~~~~~~~~~~~~~~~~~~~~~~

Gore's Granny Fairy: renderGrannyGoreF(obj,type);
type = 1, Blue
type = 2, Red

Gore's Redhead Fairy: renderRedheadGoreF(obj,type);
type = 1, Blue
type = 2, Red

Gore's Sunflower Fairy: renderSunflowerGoreF(obj);

Gore's Tiny Fairy: renderTinyGoreF(obj,type);
type = 1, Blue
type = 2, Red
type = 3, Green
type = 4, Yellow
type = 5, Purple


NON-TOUHOU
~~~~~~~~~~

Tenebris (belongs to TheGuyNoOneRemembers on DeviantArt): renderTenebris(obj);

