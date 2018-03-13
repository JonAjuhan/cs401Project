











Originally, you had to surround the codes with $<code>$, but this was a horrible mess
So instead, you surround the code with (<code>). I haven't changed the stuff below so it still says $...

Treat the code as unprinted text. You can make "comments" by just surrounding it in parenthesis.



	
	

Optional Simple Commands (defaulted only initially)
	$PA-Z - Path to the image, RELATIVE to the main script directory
	$IA-Z - Side the image is on (L for left, R for right; $SAR puts image A on Right)
	
	$SF - Size of font
	$SB - Bold the text (0 - false, 1 - true)
	$SX - X width Letter spacing
	$SY - Y width letter spacing
	$SD - Text entrance delay between letters
	$ST - Text entrance time, in frames
	$SS - Scale multiplier of the letter
	$SE - Name for the sound effect to use when the text enters
	$SQ - Force the current text delay factor to specified number
	
	$TA - Text top RGB value (seperate with |)
	$TR - Text top Red Value
	$TG - Text top Green Value
	$TB - Text top Blue value
	
	$BR - Text bottom Red Value
	$BG - Text bottom Green Value
	$BB - Text bottom Blue value
	
	$OS - Border size (if 0, no border)
	$OT - Border type (0 - none, 1 - full outline, 2 - shadow)
	$OR - Border Red Value
	$OG - Border Green Value
	$OB - Border Blue value
	
	
	$DB - Dialogue Box image path, defaults to a black box
	$DF - Dialogue foreground image path, defaults to stars
	$DO - Dialogue border image path, defaults to a solid black image
	$DV - Dialogue border vertex count, defaults to 8 (defaults to 8 if below 8)
	$DA - Dialogue border alpha, defaults to 255
	

Other Commands

Save: $ZSAVE
	A - Z: Save current settings to specified cutin
				These settings will load when the specified cutin becomes active.

Font: $ZFONT
	Uses the given font name. Must be installed using InstallFont prior
	"Source Code ProDNHEDIT" is the included one.
	
	
Timing: $ZTIME
	0. Until player presses key
	1. Until Given time ($TIME1#, where # is the number of frames)
	2. Until player presses key or given time ($TIME2#)
	3. Until player presses key, after given time ($TIME3#)
	4. Until scripter uses ForceDialogueOff

Intro Text type: $ZENTR 
	0. Instant
	1. Fade in
	2. Sharp grow in
	3. Sharp grow down + fade in
	
	not implemented yet
	4. Ghostly 'spirited away' (make another 2 text objects that fire diagonal and fade away)

Idle Text type: $ZIDLE
	- Example: (of Wavy input)
	"(ZIDLE2|4|8|215)"

	0. Normal
	1. Shaking;  	Intensity
	2. Wavy;  		Intensity|Rate|Angle
	3. Unsettle		Intensity
	
	not implemented yet
	4. Sine Rotate text|Intensity|Rate
	5. Sine Scale text|Intensity|Rate

Cutin Animations (upon advancement of dialogue): $ZCANM
	not implemented yet
	0. Nothing
	1. Violent shake (like yoshika losing)
	2. Grow and move like in a cupping motion



#
$