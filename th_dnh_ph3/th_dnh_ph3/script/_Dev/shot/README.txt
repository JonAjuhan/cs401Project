*******************************************************************
*	AllStar Danmakufu ShotSheet by Ozzy/ExPorygon (v1.0)	  *
*******************************************************************

This shotsheet imitations of ZUN bullets from a nico user: ごれ (http://commons.nicovideo.jp/user/40336)
As such, these bullets, unlike ZUN's, are (to my knowledge) free to use and distribute with Danmakufu projects.
All commonly used bullet types from Touhou games are included, along with Raiko's lighting lasers and the Tsukumo music note bullets.

In order to optimize the shot graphics for use with Danmakufu, many edits to many of the bullet types (usually slight resizing) were made.
Several additional shot types were also added, including:
	-Large Round Bullets from in PCB style
	-An alternate style of Dark Pellets made by inverting the normal pellets
	-A custom delay cloud

Instructions:
	-Include 'AllStarShot_Const.dnh' with '#include' in your script.
	-Make sure that 'AllStarShot_Const.dnh', 'AllStarShot.dnh', and 'AllStarShot.png' are in the same directory.
	-Either fire the bullets with their numerical ID or use the contants in 'ZUNShot_Const.dnh'.
	-You can fire ADD variants of each bullet type by adding 500 to the normal shot id.
	-Shot IDs over 1000 are reserved for laser shots. Due to Danmakufu automatically rendering lasers in ADD, it is recommended that you only use these IDs when using lasers.
	
Thanks to:
-Helepolis for making the original ZUN expanded shot data, on which a sizeable amount of this is based.
-Daemoniken for making the PCB style large bullets.
-CK Crash for advice on the delay cloud design.