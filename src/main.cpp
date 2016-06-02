//DxLib�̎Q�l�ɂ��Ă�������
//����URL�̓T���v���v���O�����̃y�[�W�ł�
//http://dxlib.o.oo7.jp/dxprogram.html
//����URL�̓��t�@�����X�̃y�[�W�ł�
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
	//�ׂ����ݒ�F�X
	ChangeWindowMode(true);
	SetGraphMode(Window::Width, Window::Height, 32);
	SetWindowSizeChangeEnableFlag(TRUE);
	SetWindowSizeExtendRate(1.0);
	//�w�i�̐F�ւ�
	//SetBackgroundColor(255, 255, 255);

	int ModelHandle;

	// �c�w���C�u��������������(�G���[���N�����璼���ɏI��)
	if (DxLib_Init() == -1)		return -1;			

	//�E����ʂɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);

	ModelHandle = MV1LoadModel("res/car04.mqo");	
	
	MV1SetPosition(ModelHandle, VGet(200.0f, -200.0f, 600.0f));

	//���C�����[�v
	//while��()�ɂ���ProcessMessage�������ƁA����ɓ����Ȃ��Ȃ�
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();			//��ʂ���������

		
		MV1DrawModel(ModelHandle);

		
		ScreenFlip();				//�I���e��ʂƃE����ʂ����ւ���
	}

	//�c�w���C�u�����g�p�̏I������
	DxLib_End();

	//�\�t�g�̏I�� 
	return 0;
}