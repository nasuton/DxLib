//DxLibの参考にしてください
//下のURLはサンプルプログラムのページです
//http://dxlib.o.oo7.jp/dxprogram.html
//下のURLはリファレンスのページです
//http://dxlib.o.oo7.jp/dxfunc.html

#include "DxLib.h"

enum Window
{
	Width = 1024,
	Height = 1024
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// ＤＸライブラリ初期化処理(エラーが起きたら直ちに終了)
	if (DxLib_Init() == -1)		return -1;			

	//ウラ画面に描画する
	SetDrawScreen(DX_SCREEN_BACK);

	//メインループ
	//whileの()にあるProcessMessageを消すと、正常に動かなくなる
	while (ProcessMessage() == 0) {

		//画面を消去する
		ClearDrawScreen();



		//オモテ画面とウラ画面を入れ替える
		ScreenFlip();
	}

	//ＤＸライブラリ使用の終了処理
	DxLib_End();

	//ソフトの終了 
	return 0;
}