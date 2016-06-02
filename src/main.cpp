//DxLibの参考にしてください
//下のURLはサンプルプログラムのページです
//http://dxlib.o.oo7.jp/dxprogram.html
//下のURLはリファレンスのページです
//http://dxlib.o.oo7.jp/dxfunc.html

#include "DxLib.h"
#include "DxLib_Sub.h"

enum Window
{
	Width = 2048,
	Height = 2048
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//細かい設定色々
	ChangeWindowMode(true);
	SetGraphMode(Window::Width, Window::Height, 32);
	SetWindowSizeChangeEnableFlag(TRUE);
	SetWindowSizeExtendRate(1.0);
	//背景の色替え
	//SetBackgroundColor(255, 255, 255);

	int ModelHandle;

	// ＤＸライブラリ初期化処理(エラーが起きたら直ちに終了)
	if (DxLib_Init() == -1)		return -1;			

	//ウラ画面に描画する
	SetDrawScreen(DX_SCREEN_BACK);

	ModelHandle = MV1LoadModel("res/car04.mqo");	
	
	MV1SetPosition(ModelHandle, VGet(200.0f, -200.0f, 600.0f));

	//メインループ
	//whileの()にあるProcessMessageを消すと、正常に動かなくなる
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();			//画面を消去する

		
		MV1DrawModel(ModelHandle);

		
		ScreenFlip();				//オモテ画面とウラ画面を入れ替える
	}

	//ＤＸライブラリ使用の終了処理
	DxLib_End();

	//ソフトの終了 
	return 0;
}