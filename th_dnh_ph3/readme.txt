右端で折り返さないほうが読みやすいです。 
I think this is saying to disable word wrap? It literally says "it is easier to not fold at the right edge".


○DnhViewerについて。"About DnhViewer,"
　スクリプトを直接再生するツールです。 "It is a tool to play scripts directly."
　自機スクリプトと敵スクリプトをドラッグ＆ドロップで登録し "Select player script and enemy script"
　再生できます。 "You can play it"
(DnhViewer is a program to load/run individual script files, bypassing Danmakufu's menu. For the time being, we don't have too much use for it, but once we set up a proper title screen with just the usual options (Start Game/Practice Start/Extra Start/.../Config/Exit Game) it'll be good for testing individual singles and such.)

　サンプルでは以下を含めています。
　自機：/script/player/default_player/Default_Player_Rumia.txt
　敵：/script/ExRumia/ExRumiaSpell01.txt
      /script/ExRumia/ExRumia_Plural.txt
      /script/ExRumia/ExRumia_Stage.txt
This is just saying what example scripts are included.

○本ソフトはフリーソフトです。
　アプリケーションを用いて発生した損害などの保証はいっさいできません。
　自己責任でお願いします。
"This is free software.
We cannot guarantee damages/etc caused by the application.
Please take responsibility for your actions."


○インストール方法
　適当な場所に圧縮ファイルを展開してください。
"Installation:
Unzip it to a suitable place."

○アンインストール方法
　フォルダごと削除してください。レジストリは使ってません。
"Uninstallation:
Just delete it. I don't use the registry."

○キーボード操作 "Keyboard operation"
　　カーソルキー：移動 "Cursor keys: move"
　　Z：弾(押しっぱなしでオート連射)、決定 "Z key: shoot(hold), confirm"
　　X：ボム、キャンセル "X key: bomb, cancel"
　　左Shift：減速移動 "Shift key: Slow down"
　　左Ctrl：高速再生 "Ctrl key: Fast-forward"
　　R：リセット(タイトル画面に戻る) "R: Reset" (it says "return to title screen", but actually it reloads the current script, and only when pressed on the pause screen, and only because I specifically made it do that.)
　　BackSpace：リトライ "Backspace: Retry" (that's weird and will be removed when I get around to it - the convention is R while paused)

